#include <iostream>

#include "linux/v4l2-ext-avd.h"
#include "linux/v4l2-ext-vbi.h"
#include "linux/v4l2-ext-component.h"
#include "linux/v4l2-ext-hdmi.h"
#include "linux/v4l2-ext-earc.h"




using namespace std;

int main()
{
    cout << "build locally and check build time syntax error" << endl;
    cout << "How to build : $g++ -I. header-verify.cpp" << endl;
    v4l2_ext_hdmi_edid edid;

    edid.port = V4L2_EXT_HDMI_INPUT_PORT_1;

    cout << edid.port << endl;

    return 0;
}

