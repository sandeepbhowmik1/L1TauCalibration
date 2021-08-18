from ROOT import *

fIn = TFile.Open('plots_9x9.root')
hSig = fIn.Get('Eiso_20_30_sig')
hBkg = fIn.Get('Eiso_20_30_bkg')

gr = TGraph()

for i in range (0, hSig.GetNbinsX()):
    sigEff = hSig.Integral(-1, i) / hSig.Integral(-1, -1)
    bkgEff = 1. - (hBkg.Integral(-1, i) / hBkg.Integral(-1, -1))
    print sigEff, bkgEff, hSig.Integral(-1, i) , hBkg.Integral(-1, i) 
    gr.SetPoint(i, sigEff, bkgEff)

c1 = TCanvas()
gr.Draw("APL")
c1.Update()
fOut = TFile ("ROC_9x9.root" , "recreate")
gr.SetName("gr")
gr.Write()
# raw_input()
