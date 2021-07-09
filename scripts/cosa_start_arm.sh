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
BBHM_CUR_CFG="/nvram/bbhm_cur_cfg.xml"
source /etc/utopia/service.d/log_env_var.sh
source /etc/utopia/service.d/log_capture_path.sh
source /etc/device.properties

print_uptime "cosa_service_start"

ulimit -c unlimited
if [ "$BUILD_TYPE" != "prod" ]; then
      echo /tmp/%t_core.prog_%e.signal_%s > /proc/sys/kernel/core_pattern
fi

if [ -f /etc/mount-utils/getConfigFile.sh ];then
   . /etc/mount-utils/getConfigFile.sh
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

#
#	Allow custom plug-ins
#
if [ -f "$PWD/cosa_start_custom_1.sh" ]; then
	./cosa_start_custom_1.sh
fi

export LD_LIBRARY_PATH=$PWD:.:$PWD/../../lib:$PWD/../../.:/lib:/usr/lib:$LD_LIBRARY_PATH
export DBUS_SYSTEM_BUS_ADDRESS=unix:path=/var/run/dbus/system_bus_socket
export LOG4C_RCPATH=/etc
export BOX_TYPE ATOM_ARPING_IP

#zqiu: update the bbhm for 2.1s11
if [ "$BOX_TYPE" = "XB3" ]; then
    /usr/ccsp/psm/bbhm_patch.sh -f /nvram/bbhm_cur_cfg.xml
else
    echo "bbhm patch is not required for other platforms"
fi

cp ccsp_msg.cfg /tmp

# have IP address for dbus config generated
#./DbusCfg
if [ "$MANUFACTURE" != "Technicolor" ] && [ "$BOX_TYPE" != "XB3" ]; then
	$BINPATH/dbus-daemon --config-file=./basic.conf --fork
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

sleep 5

if [ -e ./notify-comp ]
then
	cd notify-comp
	echo "$BINPATH/notify_comp -subsys $Subsys"
	$BINPATH/notify_comp -subsys $Subsys
	cd ..
fi

if [ -e ./cm ]
then
	cd cm
	echo_t "$BINPATH/CcspCMAgentSsp -subsys $Subsys"
	$BINPATH/CcspCMAgentSsp -subsys $Subsys
	cd ..
fi

if [ -e ./pam ]
then
	cd pam
	echo "$BINPATH/CcspPandMSsp -subsys $Subsys"
	$BINPATH/CcspPandMSsp -subsys $Subsys
	cd ..
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
