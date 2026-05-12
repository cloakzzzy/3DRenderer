import os 
from datetime import datetime 

files = ""
commit_message = "Rendered triangles on multiple windows" 
for i in os.listdir():
	type = i.split('.')[-1]
	if type == "cpp" or type == "hpp" or type == "h" or type == "vert" or type == "frag" or type == "txt":
		files += i + " "
	
os.system(f"git add {files}")
os.system(f'git commit -m "{commit_message}"')
os.system(f"git push origin main --force")