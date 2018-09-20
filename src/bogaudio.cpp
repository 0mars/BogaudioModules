
#include "bogaudio.hpp"

#include "AD.hpp"
#include "ADSR.hpp"
#include "Additator.hpp"
#include "AMRM.hpp"
#include "Analyzer.hpp"
#include "Bool.hpp"
#include "Cmp.hpp"
#include "CVD.hpp"
#include "DADSRH.hpp"
#include "DADSRHPlus.hpp"
#include "DGate.hpp"
#include "Detune.hpp"
#include "EightFO.hpp"
#include "FMOp.hpp"
#include "FlipFlop.hpp"
#include "Follow.hpp"
#include "LFO.hpp"
#include "Lag.hpp"
#include "Lmtr.hpp"
#include "Manual.hpp"
#include "Matrix88.hpp"
#include "Mix4.hpp"
#include "Mix8.hpp"
#include "Mult.hpp"
#include "Mute8.hpp"
#include "Noise.hpp"
#include "Nsgt.hpp"
#include "Offset.hpp"
#include "Pan.hpp"
#include "Pressor.hpp"
#include "Reftone.hpp"
#include "SampleHold.hpp"
#include "Shaper.hpp"
#include "ShaperPlus.hpp"
#include "Stack.hpp"
#include "Sums.hpp"
#include "Switch.hpp"
#include "UMix.hpp"
#include "VCA.hpp"
#include "VCAmp.hpp"
#include "VCM.hpp"
#include "VCO.hpp"
#include "VU.hpp"
#include "XCO.hpp"
#include "XFade.hpp"

#include "Test.hpp"
#include "Test2.hpp"
#include "template_panels.hpp"

//NEW_INCLUDES_HERE

Plugin *plugin;

void init(rack::Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);
	p->website = "https://github.com/bogaudio/BogaudioModules";
	p->manual = "https://github.com/bogaudio/BogaudioModules/blob/master/README.md";

	p->addModel(modelVCO);
	p->addModel(modelXCO);
	p->addModel(modelAdditator);
	p->addModel(modelFMOp);

	p->addModel(modelLFO);
	p->addModel(modelEightFO);

	p->addModel(modelDADSRH);
	p->addModel(modelDADSRHPlus);
	p->addModel(modelDGate);
	p->addModel(modelShaper);
	p->addModel(modelShaperPlus);
#ifdef EXPERIMENTAL
	p->addModel(modelAD);
#endif
	p->addModel(modelADSR);
	p->addModel(modelFollow);

	p->addModel(modelMix4);
	p->addModel(modelMix8);
	p->addModel(modelVCM);
#ifdef EXPERIMENTAL
	p->addModel(modelUMix);
	p->addModel(modelMatrix88);
	p->addModel(modelMute8);
#endif
	p->addModel(modelPan);
	p->addModel(modelXFade);
	p->addModel(modelVCA);
	p->addModel(modelVCAmp);

#ifdef EXPERIMENTAL
	p->addModel(modelAMRM);
	p->addModel(modelPressor);
	p->addModel(modelLmtr);
	p->addModel(modelNsgt);
#endif

	p->addModel(modelAnalyzer);
	p->addModel(modelVU);

	p->addModel(modelDetune);
	p->addModel(modelStack);
	p->addModel(modelReftone);

	p->addModel(modelBool);
#ifdef EXPERIMENTAL
	p->addModel(modelCmp);
#endif
	p->addModel(modelCVD);
	p->addModel(modelFlipFlop);
	p->addModel(modelManual);
	p->addModel(modelMult);
	p->addModel(modelNoise);
	p->addModel(modelOffset);
	p->addModel(modelSampleHold);
	p->addModel(modelSums);
	p->addModel(modelSwitch);

#ifdef EXPERIMENTAL
	p->addModel(modelLag);
#endif

#ifdef TEST
	p->addModel(modelTest);
	p->addModel(modelTest2);

	p->addModel(modelThreeHP);
	p->addModel(modelSixHP);
	p->addModel(modelEightHP);
	p->addModel(modelTenHP);
	p->addModel(modelTwelveHP);
	p->addModel(modelThirteenHP);
	p->addModel(modelFifteenHP);
	p->addModel(modelEighteenHP);
	p->addModel(modelTwentyHP);
	p->addModel(modelTwentyTwoHP);
	p->addModel(modelTwentyFiveHP);
	p->addModel(modelThirtyHP);
#endif

	//NEW_MODELS_HERE
}
