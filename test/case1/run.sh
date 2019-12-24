XSC=../../build/xsc

pushd ../..
make clean
make -j8
popd

#../../build/xsc --comments ON --reflect ON --show-ast ON -T frag -E main --version-in HLSL5 --version-out GLSL450 -D__NVN__ Fxaa.psh
#../../build/xsc -PP -T frag -E main --version-in HLSL5 --version-out GLSL450 -D__NVN__ Fxaa.psh -o fxaa.pp

#OPT="--comments ON --reflect ON --show-ast ON"
OPT=""

gcc -x c -D__NVN__ -E Fxaa.psh -o fxaa.pp.psh && $XSC $OPT -T frag -E main --version-in HLSL5 --version-out GLSL450 -D__NVN__ fxaa.pp.psh