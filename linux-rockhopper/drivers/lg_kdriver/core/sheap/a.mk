
headers_sheap := kdriver_sheap:*.h
$(foreach p,$(headers_sheap),$(eval $(call install_headers,$(p))))
