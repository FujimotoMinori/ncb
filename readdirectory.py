import ROOT
from array import array
from ROOT import TCanvas
from ROOT import *

# ATLAS Style
#ROOT.gROOT.LoadMacro("/nfs/dust/atlas/user/jeongj/atlas_Style/AtlasUtils.C")
#ROOT.gROOT.LoadMacro("/nfs/dust/atlas/user/jeongj/atlas_Style/AtlasStyle.C")
#ROOT.gROOT.LoadMacro("/nfs/dust/atlas/user/jeongj/atlas_Style/AtlasLabels.C")

#SetAtlasStyle()

f = ROOT.TFile("NoiseMap_00352123_calibration_PixelNoise_daq_190808_1226.root")

hnames = []

# key here is the histogram. Get list of names of the histograms and put it in an array called hnames.
for key in f.GetListOfKeys():
    n = key.GetName()
    # here one can put if statement to select specific histograms containing/starting/ending a word "A"
    hnames += [n]


# To select histograms, instead of using for loop of the list of keys, one can specify each names of the histogram. For example,
'''
hnames += "my-histogram1"
hnames += "my-histogram2"
'''
# Or directly use t1 = f.Get("my-histogram1"), t2 = f.Get("my-histogram2") in the below for loop

# for loop of histograms
for i in range(len(hnames)):
    c = TCanvas("c_%s" %(i)) # for each histogram, make a canvas named "c_histogram"
    t = f.Get(hnames[i])     # t is the histogram object: TH1 or TH2

    t.SetStats(0)            # 0: do not show statistics box

    #Scatter plot
    #t.SetMarkerStyle(20) # 20 as default; 7 = full dot medium
    #t.SetMarkerColor(1)  # 1 = kBlack
    #t.Draw("p")

    t.Draw()        # colz option is to draw a colourful 2D histograms.
    t.GetYaxis().SetTitleOffset(1.4)  # set the position of the Label of Y axis away from the Y axis.
    t.GetZaxis().SetTitle("Average rate [Hz]") # Z axis is defined for 2D histogram, the palette axis.
    t.GetYaxis().SetTitleOffset(1.4)  # set the position of the Label of Y axis away from the Y axis.
    t.GetZaxis().SetTitle("Average rate [Hz]") # Z axis is defined for 2D histogram, the palette axis.
    t.GetZaxis().SetTitleOffset(1.2) # set the position of the Label of palette(Z) axis.
    gStyle.SetPalette(1)             # 1: default colour scheme for 2D histogram. Specify in case in use of ATLAS style as the colour is set differently.
    gStyle.SetPadLeftMargin(0.15)
    gStyle.SetPadRightMargin(0.20)
    #ROOT.ATLASLabel(0.6, 0.87, "internal", ROOT.kBlack) # must be put after t.Draw() as it is written on

    #c.SetLogy();         # Set log scale for Y axis in the canvas.
    c.Update()
    c.Print("%s.eps" %(hnames[i]), 'eps') # Save the figure in the 'eps' format.

