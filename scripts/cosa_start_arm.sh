#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2015 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
#######################################################################
#   Copyright [2014] [Cisco Systems, Inc.]
# 
#   Licensed under the Apache License, Version 2.0 (the \"License\");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
# 
#       http://www.apache.org/licenses/LICENSE-2.0
# 
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an \"AS IS\" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#######################################################################

BINPATH="/usr/bin"
BBHM_CUR_CFG="/tmp/bbhm_cur_cfg.xml"
source /etc/utopia/service.d/log_env_var.sh
source /etc/utopia/service.d/log_capture_path.sh
source /etc/device.properties

set_tz() {
    timezone=$(syscfg get TZ)
    if [ $timezone ]
    then
        export TZ=$timezone
    fi
}

set_tz

print_uptime "cosa_service_start"

if [ -f /etc/mount-utils/getConfigFile.sh ];then
   . /etc/mount-utils/getConfigFile.sh
fi

if [ "x"$1 = "xstop" ]; then 
   # systemd initiates a SIGTERM upon shutdown for services in reverse order
   # Platforms which still starts services with cosa_start.sh from systemd, 
   # shutdown sequence has to be explicitly initiated 
   killall telemetry2_0
   killall CcspPandMSsp
   killall CcspCMAgentSsp
   killall PsmSsp
   killall CcspCrSsp 
   exit 0
fi

if [ "x"$1 = "xkill" ] || [ "x"$2 = "xkill" ]; then
	killall ccspRecoveryManager
	sleep 3
	killall CcspTandDSsp
	killall CcspDnsSsp
#	killall CcspFuSsp
#	killall CcspSsdSsp
	killall CcspPandMSsp
	killall CcspTr069PaSsp
	killall PsmSsp
#	killall CcspRmSsp
	killall CcspCrSsp
#    killall CcspLmSsp
	killall CcspMtaAgentSsp
	killall CcspCMAgentSsp
    killall CcspLMLite
    killall CcspXdnsSsp
	killall webpa
fi

export LD_LIBRARY_PATH=$PWD:.:$PWD/../../lib:$PWD/../../.:/lib:/usr/lib:$LD_LIBRARY_PATH
export BOX_TYPE ATOM_ARPING_IP

if [ "$BUILD_TYPE" = "prod" ] || [ "$BOX_TYPE" = "MV3" ]
then
	echo '|/bin/false' >/proc/sys/kernel/core_pattern
	ulimit -c 0
else
	echo "|/usr/ccsp/core_compress.sh %p %e %s" >/proc/sys/kernel/core_pattern
	ulimit -c unlimited
fi

cp ccsp_msg.cfg /tmp

/usr/bin/rbus_session_mgr &

if [ "$BOX_TYPE" = "MV1" ]
then
	HOST_AND_PORT=$(awk -F "[><=,]" '/<listen>/ { print $4 ":" $6 }' /usr/ccsp/basic.conf)
	/usr/bin/rtrouted -s tcp://$HOST_AND_PORT
else
	/usr/bin/rtrouted -s unix:///tmp/rtrouted
fi

mkdir -p $LOG_PATH

touch /tmp/cp_subsys_ert

Subsys="eRT."

# Remove all disable flags
if [ -e /nvram/disablewecb ]; then
	echo "***Removing all disable flags*****"
        rm -rf /nvram/disable*
fi

echo "Elected subsystem is $Subsys"

if [ "$CR_IN_PEER" != "yes" ]
then
	echo "$BINPATH/CcspCrSsp -subsys $Subsys"
	$BINPATH/CcspCrSsp -subsys $Subsys
fi

echo "$BINPATH/PsmSsp -subsys $Subsys"
$BINPATH/PsmSsp -subsys $Subsys


if [ -e ./notify-comp ]
then
	cd notify-comp
	echo "$BINPATH/notify_comp -subsys $Subsys &"
	$BINPATH/notify_comp -subsys $Subsys &
	cd ..
fi

if [ -e ./cm ]
then
	cd cm
	echo_t "$BINPATH/CcspCMAgentSsp -subsys $Subsys &"
	$BINPATH/CcspCMAgentSsp -subsys $Subsys &
	cd ..
fi

if [ -e ./pam ]
then
	cd pam
	echo "$BINPATH/CcspPandMSsp -subsys $Subsys &"
	$BINPATH/CcspPandMSsp -subsys $Subsys &
	cd ..
fi

# Enable XCONF Conf config fetch
if [ -f  /lib/rdk/dcm.service ]; then
    echo_t "DCM SCRIPT: Calling dcm.service"
    /bin/sh /lib/rdk/dcm.service &
fi

if [ -e /usr/bin/wanmanager ]
then
    /usr/bin/wanmanager -subsys $Subsys &
fi

if [ -e /usr/bin/VlanManager ]
then
    /usr/bin/VlanManager -subsys $Subsys &
fi

#Mesh-596: We need to start dropbear a bit earlier so that lease sync happens
#for plume
if [ "x$MULTI_CORE" == "xyes" ]; then
    echo "starting dropbear"
        mkdir -p /tmp/.dropbear
    DROPBEAR_PARAMS_1="/tmp/.dropbear/dropcfg1$$"
    DROPBEAR_PARAMS_2="/tmp/.dropbear/dropcfg2$$"
    getConfigFile $DROPBEAR_PARAMS_1
    getConfigFile $DROPBEAR_PARAMS_2
    dropbear -r $DROPBEAR_PARAMS_1 -r $DROPBEAR_PARAMS_2 -E -s -p $ARM_INTERFACE_IP:22 -P /var/run/dropbear_ipc.pid > /dev/null 2>&1 &

fi

if [ -f "/usr/sbin/tdkb_launcher.sh" ]
then
    echo "Found TDK-B launcher script!!!"
    echo "Invoking TDK-B launcher script!!!"
    sh /usr/sbin/tdkb_launcher.sh &
fi
