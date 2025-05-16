import os 

# set working directory to C:\Users\joshu\Documents\personal_vsc_2\projects\Project_F14_Tomcat
try:
    os.chdir(r'C:\\Users\\joshu\Documents\\personal_vsc_2\\projects\\Project_F14_Tomcat')
except FileNotFoundError:
    os.chdir(r"c:\\Users\\Josh\Documents\\VSC\DCS\\Project_F14_Tomcat")

seats = ["Pilot", "RIO"]

print("[1] Pilot\n[2] RIO\n")
seat = input("Select your seat: ")

name = input("Enter module name: ")

module = name.replace(" ", "_")

# Base path for module
module_path = f"Modules\\{seats[int(seat) - 1]}\\{module}"

os.mkdir(module_path)

os.mkdir(f"{module_path}\\BIOS_TESTING")
os.mkdir(f"{module_path}\\BIOS_TESTING\\bak")
os.mkdir(f"{module_path}\\BIOS_TESTING\\individual")
os.mkdir(f"{module_path}\\BIOS_TESTING\\individual_alone")

os.mkdir(f"{module_path}\\C")

os.mkdir(f"{module_path}\\hardware")
os.mkdir(f"{module_path}\\hardware\\other")
os.mkdir(f"{module_path}\\hardware\\switches")

os.mkdir(f"{module_path}\\schematics")
os.mkdir(f"{module_path}\\schematics\\model_files")
