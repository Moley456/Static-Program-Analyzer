import os
import xml.etree.ElementTree as ET

# src = os.listdir(r_path)
# src = os.listdir(os.path.join("Team06", "Tests06", "systemtests"))
r_path = 'Team06\Tests06\systemtests'
src = os.listdir(r_path)
error = False

for entry in src:
    subdir_path = os.path.join(r_path, entry)
    if os.path.isdir(subdir_path):
        subdir_entries = os.listdir(subdir_path)
        for subentry in subdir_entries:
            if subentry.endswith('.xml'):
                subentry_path = os.path.join(subdir_path, subentry)
                tree = ET.parse(subentry_path)

                root = tree.getroot()

                xml_string = ET.tostring(root, encoding='utf8', method='xml')

                if xml_string.find(b'failed') != -1:
                    error = True
                    print(
                        '{}/{} has a failing test case!'.format(entry, subentry))
                elif xml_string.find(b'timeout') != -1:
                    error = True
                    print(
                        '{}/{} has a test case which timeouts!'.format(entry, subentry))

if error:
    raise Exception('One or more system tests failed!')

print('Success, all systemtests passes!')
