#include <cstdlib>
#include <vector>
#include <CL/cl_platform.h>

std::vector<std::vector<cl_int>> getSunglassData() {

    std::vector<std::vector<cl_int>> ret =
            {{
                     {1202, 1124, 1232, 1250, 157979},
                     {1200, 414, 1232, 1246, 160741},
                     {1201, 1124, 1233, 1241, 157654},
                     {1201, 1124, 1233, 1247, 157652},
                     {1219, 415, 1232, 1250, 158696},
                     {1200, 414, 1232, 1247, 158828},
                     {1200, 414, 1229, 1237, 160727},
                     {1200, 414, 1232, 1237, 160728},
                     {1201, 1124, 1231, 1250, 157580},
                     {1201, 415, 1232, 1248, 157574},
                     {1219, 415, 1234, 1249, 157549},
                     {1200, 415, 1232, 1250, 157539},
                     {1202, 415, 1234, 1250, 157538},
                     {1200, 1124, 1232, 1253, 157533},
                     {1200, 415, 1233, 1250, 157532},
                     {1200, 415, 1234, 1250, 157530},
                     {1200, 1124, 1232, 1250, 160734},
                     {1201, 415, 1230, 1248, 158585},
                     {1202, 415, 1234, 1253, 158642},
                     {1201, 415, 1230, 1250, 157567},
                     {1200, 414, 1232, 1247, 160744},
                     {1201, 414, 1234, 1246, 160743},
                     {1201, 414, 1231, 1250, 157223},
                     {1201, 415, 1234, 1250, 158031},
                     {1201, 414, 1233, 1246, 157451},
                     {1201, 414, 1230, 1246, 160719},
                     {1202, 414, 1229, 1247, 160718},
                     {1202, 415, 1234, 1248, 162346},
                     {1202, 1124, 1234, 1253, 162352},
                     {1200, 414, 1229, 1247, 162353},
                     {1201, 415, 1230, 1249, 162354},
                     {1201, 414, 1230, 1241, 160720},
                     {1201, 1124, 1231, 1253, 159707},
                     {1201, 415, 1234, 1250, 159677},
                     {1201, 1124, 1232, 1241, 159664},
                     {1201, 415, 1230, 1253, 159355},
                     {1202, 414, 1233, 1246, 160732},
                     {1202, 414, 1233, 1241, 160873},
                     {1200, 415, 1234, 1250, 158963},
                     {1200, 415, 1234, 1250, 158950},
                     {1200, 415, 1232, 1250, 158946},
                     {1200, 415, 1232, 1248, 158926},
                     {1200, 415, 1232, 1250, 158922},
                     {1200, 415, 1232, 1250, 158919},
                     {1200, 415, 1234, 1248, 158913},
                     {1201, 415, 1230, 1253, 159300},
                     {1200, 415, 1234, 1248, 158806},
                     {1200, 414, 1229, 1250, 160738},
                     {1200, 414, 1229, 1237, 160739},
                     {1202, 414, 1233, 1250, 160872},
                     {1200, 415, 1234, 1248, 158814},
                     {1200, 1124, 1232, 1246, 160736},
                     {1202, 414, 1229, 1250, 158820},
                     {1201, 414, 1233, 1241, 159700},
                     {1202, 414, 1229, 1246, 160721},
                     {1200, 414, 1229, 1247, 160747},
                     {1200, 414, 1232, 1250, 160748},
                     {1201, 415, 1232, 1250, 158206},
                     {1201, 414, 1233, 1250, 158464},
                     {1201, 414, 1230, 1241, 158463},
                     {1201, 414, 1230, 1241, 158462},
                     {1201, 1124, 1230, 1247, 158460},
                     {1202, 414, 1233, 1241, 160733},
                     {1202, 414, 1229, 1250, 160723},
                     {1200, 414, 1229, 1247, 160725},
                     {1201, 1124, 1230, 1243, 158579},
                     {1200, 415, 1234, 1250, 158475},
                     {1202, 1124, 1233, 1250, 158476},
                     {1202, 1124, 1233, 1248, 158450},
                     {1200, 415, 1232, 1247, 158449},
                     {1200, 415, 1232, 1250, 158448},
                     {1202, 414, 1230, 1241, 158447},
                     {1200, 1124, 1232, 1246, 158446},
                     {1200, 414, 1233, 1241, 158445},
                     {1200, 414, 1232, 1241, 158444},
                     {1200, 414, 1229, 1237, 158443},
                     {1202, 415, 1231, 1253, 158441},
                     {1202, 415, 1234, 1253, 158474},
                     {1201, 415, 1230, 1250, 158473},
                     {1202, 414, 1229, 1247, 160745},
                     {1200, 414, 1229, 1242, 158851},
                     {1200, 414, 1229, 1241, 160746},
                     {1201, 1124, 1232, 1247, 160742},
                     {1202, 414, 1233, 1250, 158472},
                     {1200, 414, 1232, 1247, 160731},
                     {1200, 414, 1232, 1246, 160730},
                     {1200, 414, 1232, 1250, 160729},
                     {1200, 415, 1232, 1250, 158834},
                     {1200, 414, 1229, 1237, 160724},
                     {1200, 414, 1232, 1241, 160740},
                     {1202, 415, 1233, 1250, 158867},
                     {1201, 415, 1234, 1253, 158482},
                     {1201, 415, 1230, 1250, 158483},
                     {1202, 415, 1232, 1242, 158705},
                     {1201, 415, 1230, 1250, 160874},
                     {1202, 414, 1229, 1250, 160722},
                     {1201, 414, 1233, 1246, 158022},
                     {1201, 414, 1230, 1237, 160948},
                     {1202, 414, 1233, 1250, 160949},
                     {1201, 1124, 1233, 1243, 158017},
                     {1202, 415, 1234, 1250, 158627},
                     {1202, 1124, 1233, 1248, 157986},
                     {1200, 414, 1229, 1250, 160726},
                     {1200, 415, 1234, 1250, 158905},
                     {1200, 1124, 1232, 1250, 158804},
                     {1201, 415, 1232, 1242, 158539},
                     {1201, 414, 1233, 1241, 157977},
                     {1202, 415, 1232, 1250, 157542},
                     {1202, 414, 1229, 1250, 158649},
                     {1202, 414, 1229, 1250, 157578},
                     {1201, 415, 1234, 1250, 157553},
                     {1200, 415, 1232, 1248, 158811},
                     {1200, 415, 1232, 1250, 158817},
                     {1201, 1124, 1230, 1250, 158592},
                     {1200, 415, 1234, 1250, 158869},
                     {1201, 414, 1233, 1241, 158461},
                     {1201, 415, 1232, 1248, 158209},
                     {1201, 415, 1230, 1250, 159830},
                     {1201, 415, 1233, 1250, 159001},
                     {1201, 414, 1230, 1242, 159246},
                     {1201, 414, 1229, 1241, 159694},
                     {1200, 415, 1232, 1250, 158040},
                     {1201, 1124, 1233, 1245, 157707},
                     {1200, 414, 1229, 1247, 158797},
                     {1200, 415, 1232, 1250, 160894},
                     {1200, 415, 1232, 1250, 160895},
                     {1200, 415, 1232, 1250, 160896},
                     {1200, 415, 1232, 1242, 160897},
                     {1202, 415, 1232, 1243, 160898},
                     {1200, 415, 1232, 1250, 160899},
                     {1202, 414, 1229, 1246, 160900},
                     {1201, 415, 1230, 1253, 160901},
                     {1201, 415, 1230, 1250, 160902},
                     {1201, 414, 1233, 1247, 160903},
                     {1202, 414, 1233, 1241, 160950},
                     {1202, 415, 1233, 1250, 160946},
                     {1201, 414, 1231, 1247, 160947},
                     {1202, 415, 1234, 1250, 162345},
                     {1202, 415, 1234, 1250, 162344},
                     {1202, 414, 1234, 1241, 162342},
                     {1202, 415, 1234, 1250, 162341},
                     {1202, 414, 1229, 1246, 162347},
                     {1200, 415, 1232, 1250, 162340},
                     {1202, 414, 1229, 1250, 162333},
                     {1201, 415, 1233, 1242, 162332},
                     {1202, 414, 1229, 1241, 162339},
                     {1202, 414, 1231, 1250, 162348},
                     {1201, 414, 1229, 1241, 162350},
                     {1202, 414, 1229, 1246, 162351},
                     {1200, 414, 1232, 1250, 162343},
                     {1202, 414, 1229, 1241, 162337},
                     {1202, 1124, 1233, 1242, 162338},
                     {1202, 415, 1233, 1242, 162334},
                     {1202, 1124, 1233, 1250, 162336},
                     {1201, 414, 1230, 1249, 162163},
                     {1200, 414, 1229, 1247, 162164},
                     {1201, 414, 1230, 1241, 162165},
                     {1201, 414, 1234, 1241, 162166},
                     {1201, 414, 1230, 1241, 162167},
                     {1201, 414, 1230, 1245, 162168},
                     {1200, 414, 1232, 1247, 162169},
                     {1201, 414, 1232, 1249, 162170},
                     {1200, 414, 1232, 1237, 162171},
                     {1200, 414, 1232, 1250, 162172},
                     {1201, 414, 1230, 1241, 162173}
             }};

    return ret;
}

