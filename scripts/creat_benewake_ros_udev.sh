echo  'KERNEL=="ttyUSB*", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE:="0777", GROUP:="dialout",  SYMLINK+="benewake_ros"' >/etc/udev/rules.d/benewake_ros_ch340.rules

service udev reload
sleep 2
service udev restart


