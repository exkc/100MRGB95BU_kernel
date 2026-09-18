rm -rf *.lst *.h *.cmm

cat ./bus/M23_BUS_PORT_setting.cmm			>>	./shadow_rom.cmm
cat ./bus/M23_BUS_PRIORITY_setting.cmm		>>	./shadow_rom.cmm

../convert_cmm ./shadow_rom.cmm shadow_rom.h
