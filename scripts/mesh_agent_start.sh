while true
do
    if [ -f /tmp/wifi_initialized ]; then
        # Start mesh-agent
        echo "Starting Mesh agent from cosa_start.sh !!!"
        cd /usr/ccsp/mesh
        ./meshAgent -subsys eRT.
        exit
    else
        #Wait until WiFi is up
        sleep 1
    fi
done
