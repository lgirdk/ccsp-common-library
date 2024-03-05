#!/bin/bash

# Read the objects and parameters from the PandM.json file
JSON_FILE="/etc/PandM.json"
objects=$(grep -o '"name": "[^"]*"' $JSON_FILE | sed -e 's/^.*"\(.*\)".*$/\1/')
objectType=($(grep -o '"objectType": "[^"]*"' $JSON_FILE | sed -e 's/^.*"\(.*\)".*$/\1/'))
setv_flag=

process_main_object() {
    local main_object="$1"

    local object_type=$(echo "$main_object" | awk -F'"objectType":' '{print $2}' | awk -F'"' '{print $2}')
    local parameters=($(echo "$main_object" | grep -oE '(\"pname\": \")([^"]*)' | awk -F'"' '{print $4}'))

    local child_objects=$(echo "$main_object" | grep -c "\"child_objects\":")

    if [ "$child_objects" -eq 0 ]; then
        parse_parameters "$object_type" "${parameters[@]}"
    else
        echo "Child objects found for $object_type."
    fi
}

parse_parameters() {
    local object_type="$1"
    shift
    local parameters=("$@")

    if [ "$object_type" = "object" ] && [ ${#parameters[@]} -gt 0 ]; then
        for parameter in "${parameters[@]}"; do
            COMPREPLY+=($(compgen -W "$parameter" -- "$cur"))
        done        
    fi
}

execute_command() {
    command=$(echo "$words" |sed 's/\. /\./g')
    echo "Executing the command $command"
    echo `$command`
    kill -INT $$
}

_dmcli_autocomplete() {
    local cur prev words cword
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    words="${COMP_WORDS[@]}"
    cword="${COMP_CWORD}"
    case $cword in
        1)
            # Auto-complete eRT
            COMPREPLY=($(compgen -W "eRT" -- "$cur"))
            ;;
        2)
            # Auto-complete getv and setv
            COMPREPLY=($(compgen -W "getv setv" -- "$cur"))
            ;;
        3)
            if [ "${prev}" == "setv" ]; then
                setv_flag=true
            else
                setv_flag=false
            fi 
            
            if [ "${prev}" == "getv" ] || [ "${prev}" == "setv" ]; then
                # Auto-complete Device.
                if [[ "$cur" == "Device" && "${prev}" == "getv" ]]; then
                    COMPREPLY=("Device.")
                elif [[ "$cur" == "Device." && "${prev}" != "Device" ]]; then
                    COMPREPLY=("${COMPREPLY[@]}$(compgen -W " " -- "$cur")")
                else
                    COMPREPLY=("${COMPREPLY[@]}" $(compgen -W "Device." -- "$cur"))
                fi
                COMPREPLY=("${COMPREPLY[@]##*( )}")
            fi
            ;;
        4)
            if [ "${prev}" == "Device." ]; then
                # Auto-complete object names
                for obj in ${objects[@]}; do
                    COMPREPLY+=($(compgen -W "$obj" -- "$cur"))
                done
            fi
            ;;
 
        5)
            start_string="\"name\": \"$prev\","
            end_string="\"name"\"
            json_data=`sed -n "/$start_string/,/$end_string/p" $JSON_FILE`
            index=$(echo "$json_data" | grep -n "\"name\": \"$prev\"" | cut -d: -f1)
            child_objects=$(echo "$json_data" | sed -n "$index,$ p" | grep -o '"child_name": "[^"]*' | sed 's/"child_name": "//' | awk -F '"' '{print $1}')
            if [ ! -z "${child_objects[@]}" ]; then
                for itr in ${child_objects[@]}; do
                    COMPREPLY+=($(compgen -W "$itr" -- "$cur"))
                done
            fi

            # Specify the main object name to process
            main_object_name="$prev"

            # Find the specified main object in the JSON data
            specified_main_object=$(awk -v target="$main_object_name" 'BEGIN {p=0} /"name": / {if (match($0, target)) {p=1; next}} /"child_objects": / {p=0} p {print $0 | "awk -F\"pname\": \"{print $2}\""}' "$JSON_FILE")

            # Check if the specified main object exists
            if [ -n "$specified_main_object" ]; then
                process_main_object "$specified_main_object"
            else
                echo "Specified main object not found."
            fi
            ;;

        6) 
            target_child_name="$prev"
            # Check if the file exists
            if [ ! -f "$JSON_FILE" ]; then
            echo "Error: JSON file '$JSON_FILE' not found."
            exit 1
            fi

            # Find the index of the target_child_name
            index=$(grep -n "\"child_name\": \"$target_child_name\"" "$JSON_FILE" | cut -d ":" -f 1)

            # Check if the specified child_name exists
            if [ -z "$index" ]; then
                execute_command
            fi

            # Extract parameters for the specified child_name and print only pname values
            params=$(sed -n -e "/\"child_name\": \"$target_child_name\"/,/\]/p" "$JSON_FILE" | grep '"pname":' | awk -F'"' '{print $4}')
            COMPREPLY+=($(compgen -W "$params" -- "$cur"))
            ;;
        7)
            if [ "$setv_flag" == "true" ]; then
                target_pname="$prev"
                # Check if the file exists
                if [ ! -f "$JSON_FILE" ]; then
                    echo "Error: JSON file '$JSON_FILE' not found."
                    exit 1
                fi
                # Find the type of the target_pname
                type=$(grep -A1 "\"pname\": \"$target_pname\"" "$JSON_FILE" | grep -o '"type": "[^"]*' | sed 's/"type": "//')
                # Autocomplete with the type
                COMPREPLY+=($(compgen -W "$type" -- "$cur"))
            else 
                execute_command
            fi
            ;;

        8)  
            execute_command
            ;;
   esac
}
complete -F _dmcli_autocomplete dmcli
