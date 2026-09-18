
headers_kdriver := kdriver:include/*.h
headers_kdriver += kdriver/linux:include/linux/*.h
headers_kdriver += kdriver/linux/fb-ext:include/linux/fb-ext/*.h
headers_kdriver += kdriver/linux/dvbv5-ext:include/linux/dvbv5-ext/*.h
headers_kdriver += kdriver/linux/v4l2-ext:include/linux/v4l2-ext/*.h
headers_kdriver += kdriver/linux/alsa-ext:include/linux/alsa-ext/*.h
headers_kdriver += kdriver:core/aud/include/*.h
$(foreach p,$(headers_kdriver),$(eval $(call install_headers,$(p))))

dirs += core/fwload/
dirs += core/hma/
dirs += core/vdec/
dirs += core/lne/
dirs += core/sheap/

# install lowpower.sh
$(eval $(call install_files,lowpower_binary,$(src)/lowpower.sh,$(INSTALL_DIR_BIN)))
