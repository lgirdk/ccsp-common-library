import xml.etree.ElementTree as ET
import json
import sys

def parse_xml(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()

    data = []
    processed_objects = set()  

    # Iterate over each <object> element
    for obj in root.findall('.//object'):

        obj_name_element = obj.find('name')
        if obj_name_element is None:
            continue
        obj_name = obj_name_element.text

        # Check if the object has already been processed
        if obj_name in processed_objects:
            continue

        # Add the object name to the set of processed objects
        processed_objects.add(obj_name)

        obj_data = {
            "name": obj_name + '.',
            "objectType": obj.find('objectType').text,
            "parameters": [],
            "child_objects": []
        }

        # Find and process parameters if available
        parameters_element = obj.find('parameters')
        if parameters_element is not None:
            # Iterate over each <parameter> element
            for param in parameters_element.findall('parameter'):
                param_name_element = param.find('name')
                param_type_element = param.find('type')
                if param_name_element is not None and param_type_element is not None:
                    param_name = param_name_element.text
                    param_type = param_type_element.text
                    obj_data["parameters"].append({"pname": param_name, "type": param_type})

        # Check for child objects
        child_objects = obj.find('objects')
        if child_objects is not None:
            # Iterate over child <object> elements
            for child_obj in child_objects.findall('object'):
                child_obj_name_element = child_obj.find('name')
                if child_obj_name_element is None:
                    continue
                child_obj_name = child_obj_name_element.text

                # Check if the child object has already been processed
                if child_obj_name in processed_objects:
                    continue

                # Add the child object name to the set of processed objects
                processed_objects.add(child_obj_name)

                child_obj_data = {}

                # Check if 'name' and 'objectType' elements exist before accessing
                if child_obj.find('name') is not None:
                   child_obj_data["child_name"] = child_obj_name + '.'
                if child_obj.find('objectType') is not None:
                   child_obj_data["child_objectType"] = child_obj.find('objectType').text
                child_obj_data["parameters"] = []


                # Find and process parameters of child objects if available
                child_parameters_element = child_obj.find('parameters')
                if child_parameters_element is not None:
                    # Iterate over parameters of child objects
                    for param in child_parameters_element.findall('parameter'):
                        param_name_element = param.find('name')
                        param_type_element = param.find('type')
                        if param_name_element is not None and param_type_element is not None:
                            param_name = param_name_element.text
                            param_type = param_type_element.text
                            child_obj_data["parameters"].append({"pname": param_name, "type": param_type})

                obj_data["child_objects"].append(child_obj_data)

        data.append(obj_data)

    return data

parsed_data = parse_xml(sys.argv[1])

json_data = json.dumps(parsed_data, indent=4)

output_json_file = sys.argv[2]

with open(output_json_file, "w") as f:
    f.write(json_data)


