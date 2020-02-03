##cd's required because some commands use local linking
cd /home/george/Documents/Projects/Major-3D/3D-drawing/
make wipe
cd /home/george/Documents/Projects/Major-3D/Generate_Meshes/
make wipe
cd /home/george/Documents/Projects/Major-3D/Generate_Textures/
make wipe
cd /home/george/Documents/Projects/Major-3D/GPGPU/
make wipe
cd /home/george/Documents/Projects/Major-3D/3D-drawing/shaders/
printf "deleting:\n"
ls *.spv
printf "last chance to abort\npress <enter> key to proceed\n"
read keypress
rm *.spv
