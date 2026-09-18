rm -rf *.lst *.h *.cmm

cat ./bus/O26_BUS_PORT_setting.cmm        >> ./shadow_rom.cmm
cat ./bus/O26_BUS_PRIORITY_setting.cmm    >> ./shadow_rom.cmm
cat ./bus/O26_BW_Limiter_setting.cmm      >> ./shadow_rom.cmm
#cat ./tv/dummy.cmm                       >> ./shadow_rom.cmm

../convert_cmm shadow_rom.cmm shadow_rom.h

cat ./bus/O26_BUS_PORT_setting.cmm        >> ./shadow_rom_audio.cmm
cat ./bus/O26_BUS_PRIORITY_setting.cmm    >> ./shadow_rom_audio.cmm
cat ./bus/O26_BW_Limiter_setting.cmm      >> ./shadow_rom_audio.cmm
cat ./audio/O26_audio_cg.cmm              >> ./shadow_rom_audio.cmm

../convert_cmm shadow_rom_audio.cmm shadow_rom_audio.h
