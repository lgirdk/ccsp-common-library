#!/bin/sh
####################################################################################
# If not stated otherwise in this file or this component's Licenses.txt file the
# following copyright and licenses apply:

#  Copyright 2018 RDK Management

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

# http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#######################################################################################

. /etc/device.properties
. /etc/include.properties

if [ -f /etc/telemetry2_0.properties ]; then
    . /etc/telemetry2_0.properties
fi

source /etc/utopia/service.d/log_capture_path.sh
BBHM_CUR_CFG="/tmp/bbhm_cur_cfg.xml"
UTOPIA_PATH=/etc/utopia/service.d
cd /usr/ccsp/

if [ -f /etc/mount-utils/getConfigFile.sh ];then
   . /etc/mount-utils/getConfigFile.sh
fi

export LD_LIBRARY_PATH=$PWD:.:$PWD/../../lib:$PWD/../../.:/lib:/usr/lib:$LD_LIBRARY_PATH
export DBUS_SYSTEM_BUS_ADDRESS=unix:path=/var/run/dbus/system_bus_socket

if [ "x"$1 = "xstop" ]; then

   # systemd initiates a SIGTERM upon shutdown for services in reverse order
   # Platforms which still starts services with cosa_start.sh from systemd,
   # shutdown sequence has to be explicitly initiated
    killall trigger
    killall log_agent
    killall CcspAdvSecuritySsp
    killall CcspWifiSsp
    killall Harvester
    killall CcspLMLite
    killall CcspEthAgent
    killall CcspXdnsSsp
    killall CcspTandDSsp
    killall CcspMoCA
    killall CcspMtaAgentSsp
    exit 0
fi

if [ -f /tmp/cosa_start_rem_triggered ]; then
	echo_t "Already cosa_start_rem.sh script was triggered"
	exit
else
	loop_count=0
	while [ $loop_count -lt 6 ]; do
		wan_event=`sysevent get wan-status`
		if [ "$wan_event" == "started" ]; then
			break
		fi
		echo "wan-status is not started yet. sleeping for 10 sec in cosa_start_rem.sh ..."
		sleep 10
		loop_count=$((loop_count + 1))
	done

	touch  /tmp/cosa_start_rem_triggered
	echo_t "Triggered cosa_start_rem script and created tmp/cosa_start_rem_triggered file"
fi

if [ "$ENABLE_SNMPv3" = "true" ]
then
	if [ -f /lib/rdk/run_snmpv3_master.sh ]
	then
		/lib/rdk/run_snmpv3_master.sh &
	fi
fi

Subsys="eRT."

echo "Creating MESH vlans"
$UTOPIA_PATH/service_multinet_exec create_mesh_vlan &

echo_t "Elected subsystem is $Subsys"

if [ -f /lib/rdk/start-upnp-service ]
then
	/lib/rdk/start-upnp-service start &
fi

echo_t "PWD is `pwd`"

if [ -e ./mta ]
then
	cd mta
	echo_t "/usr/bin/CcspMtaAgentSsp -subsys $Subsys"
	/usr/bin/CcspMtaAgentSsp -subsys $Subsys
	cd ..
fi

if [ -e ./moca ]
then
	cd moca
	echo "/usr/bin/CcspMoCA -subsys $Subsys"
	/usr/bin/CcspMoCA -subsys $Subsys
	cd ..
fi

if [ "$1" = "pam" ] || [ "$2" = "pam" ]
then
	exit 0
fi

if [ -e ./tr069pa ]
then
	cd tr069pa
	echo_t "/usr/bin/CcspTr069PaSsp -subsys $Subsys"
	/usr/bin/CcspTr069PaSsp -subsys $Subsys
	cd ..
#	sysevent setunique GeneralPurposeFirewallRule " -A INPUT -i erouter0 -p tcp --dport=7547 -j ACCEPT "
#	sysevent setunique GeneralPurposeFirewallRule " -A INPUT ! -i erouter0 -p tcp -m tcp --dport 7547 -j DROP "
fi

if [ -e ./tad ]
then
	cd tad
	# delay TaD in order to reduce CPU overload and make PAM ready early
	echo_t "/usr/bin/CcspTandDSsp -subsys $Subsys"
	/usr/bin/CcspTandDSsp -subsys $Subsys
	cd ..
fi

if [ "$BOX_TYPE" != "TCCBR" ]
then
	echo_t "XCONF SCRIPT : Calling XCONF Client"
	/etc/firmwareSched.sh &
fi

if [ -e ./xdns ]
then
	cd xdns
	echo_t "/usr/bin/CcspXdnsSsp -subsys $Subsys &"
	/usr/bin/CcspXdnsSsp -subsys $Subsys &
	cd ..
fi

if [ -e ./ethagent ]
then
	cd ethagent
	echo_t "/usr/bin/CcspEthAgent -subsys $Subsys"
	/usr/bin/CcspEthAgent -subsys $Subsys
	cd ..
fi

if [ -e ./lm ]
then
	echo_t "***Starting CcspLMLite****"
	cd lm
	echo_t "/usr/bin/CcspLMLite -subsys $Subsys &"
	/usr/bin/CcspLMLite -subsys $Subsys &
	cd ..
fi

if [ "$BOX_TYPE" = "TCCBR" ]
then
	# Added this from cosa_start_atom.sh since in tchxb6 all Ccsp Componets are running on Arm side

	if [ -e ./harvester ]
	then
		echo_t "****STARTING HARVESTER***"
		cd harvester
		/usr/bin/harvester &
		cd ..
	fi

	if [ -e ./wifi ]
	then
		cd wifi
		echo_t "/usr/bin/CcspWifiSsp -subsys $Subsys &"
		/usr/bin/CcspWifiSsp -subsys $Subsys &
		cd ..
	fi
fi

#CBR not a best place to start here, we will end up creating bridges before
#wifi dml initialized, currently moving this to xfinity_hotspot_bridge_setup.sh
if [ "$BOX_TYPE" != "TCCBR" ]
then
	echo "bringing up XfinityWifi interfaces after all CCSP processes are up"
	xfinityenable=`psmcli get dmsb.hotspot.enable`
	if [ $xfinityenable -eq 1 ]
	then
		echo "Xfinitywifi is enabled bring up brlan2 and brlan3 if not already present"
		sysevent set hotspot-start
	else
		echo "Xfinitywifi is not enabled no need to bring up brlan2 and brlan3 interfaces"
	fi
fi

sleep 5

SELFHEAL_ENABLE=$(syscfg get selfheal_enable)
if [ "$SELFHEAL_ENABLE" = "false" ]
then
	echo_t "Running process monitoring script"
	if [ -f /etc/process_monitor.sh ];then
		/etc/process_monitor.sh &
	else
		echo "process_monitor.sh is not found"
	fi
fi

# starting the minidump watcher & uploader
if [ -f /usr/bin/inotify-minidump-watcher ]
then
	/usr/bin/inotify-minidump-watcher /minidumps /lib/rdk/uploadDumps.sh "\"\" 0" "*.dmp" &
fi

# Upload minidumps generated before the inotify call
if [ -f /lib/rdk/uploadDumps.sh ]
then
	sh /lib/rdk/uploadDumps.sh "" 0 &
fi

# Enable SSH between processors for devices having multiple processors alone
if [ "$MULTI_CORE" = "yes" ]
then
	rm -rf /telemetry/*.cmd

	if [ -f $T2_0_BIN ]
	then
		T2_ENABLE=$(syscfg get T2Enable)
	else
		echo_t "Unable to find $T2_0_BIN ... Switching T2 Enable to false !!!"
		T2_ENABLE="false"
	fi

	if [ "$T2_ENABLE" != "true" ]
	then
		/usr/bin/inotify-minidump-watcher /telemetry /lib/rdk/telemetryEventListener.sh 0 "*.cmd" &
	fi
fi

if [ -f /lib/rdk/rfc.service ]
then
	echo "Enable RFC feature"
	/bin/sh /lib/rdk/rfc.service &
fi

if [ -f /lib/rdk/rdkfwupgrader_cosa_unit.sh ]
then
	/bin/sh /lib/rdk/rdkfwupgrader_cosa_unit.sh &
fi

#RDKB-7535
if [ "$BOX_TYPE" != "TCCBR" ] && [ "$WAN_TYPE" != "EPON" ]
then
	if [ -f /rdklogger/rdkbLogMonitor.sh ]
	then
		/rdklogger/rdkbLogMonitor.sh &
	fi
fi

#TCCBR-3882: Initializing log_journal.service from here until all dependent services are implemented
if [ "$BOX_TYPE" = "TCCBR" ]
then
	/rdklogger/update_journal_log.sh &
fi

rm -rf /tmp/.dropbear

if [ "$(syscfg get telemetry_enable)" = "true" ]
then
	# Set "T2Enable" before starting the Telemetary agent.
	# The Telemetry agent receives events only if T2Enable is enabled.
	# (Fixme: why two syscfg options telemetry_enable and T2Enable?)
	syscfg set T2Enable true
	telemetry2_0 &
fi
