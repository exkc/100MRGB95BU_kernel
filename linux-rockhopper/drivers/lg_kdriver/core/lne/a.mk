
headers_lne := kdriver_lne:lne.h
$(foreach p,$(headers_lne),$(eval $(call install_headers,$(p))))

