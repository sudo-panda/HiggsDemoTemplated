# Higgs Demo Templated

This repo borrows a lot of code from [cms-opendata-analyses/HiggsExample20112012](https://github.com/cms-opendata-analyses/HiggsExample20112012)

## How to run this example template

### Prerequisites and setting up the environment
- Make sure you have docker installed

- To pull the docker container for CMSSW environment run this command in a linux terminal:
``` bash
docker run -it --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" --name="opendata" cmsopendata/cmssw_5_3_32 /bin/sh
```
When the docker container starts it will setup the environment and you will find yourself in `~/CMSSW_5_3_32/src` directory.


### Cloning and compiling
- Clone this repo in the `~/CMSSW_5_3_32/src` directory
```bash
git clone https://github.com/sudo-panda/HiggsDemoTemplated.git
```

- The EDAnalyzer is present in the `HiggsDemoTemplated/HiggsDemoAnalyzer` directory and it needs to be compiled:
```bash
cd HiggsDemoTemplated/HiggsDemoAnalyzer
scram b # compiles the EDAnalyzer
```
        
- Now you should have a working version of the `HiggsDemoAnalyzer` available in your environment. You can check this with the `edmPluginDump` command, or more useful `edmPluginDump | grep HiggsDemoAnalyzer`. You should see a printout of the HiggsDemoAnalyzerGit name twice.
    
### Running the example
- In your `HiggsDemoTemplated/Level3` directory you should see the files `demoanalyzer_cfg_level3data.py` (data example) and `demoanalyzer_cfg_level3MC.py` (Higgs simulation example)
```bash
# from HiggsDemoTemplated/HiggsDemoAnalyzer
cd ../Level3
ls
```

- run the two analysis jobs (one on data, one on MC, the input files are already predefined)
```
cmsRun demoanalyzer_cfg_level3data.py
```
will produce output file `DoubleMuParked2012C_10000_Higgs.root`
```
cmsRun demoanalyzer_cfg_level3MC.py
```
will produce output file `Higgs4L1file.root` 

- You can use the `root` command to view these two files:
```bash
root DoubleMuParked2012C_10000_Higgs.root
```
This will open the file in the root environment. To see it graphically use the following command in the root environment:

```
TBrowser b
```

Now click on the file name on the side pane. You will be able to see a Tree like symbol underneath it with the name `treegmu`. Click on that to reveal a leaf with the name `pt_gmu`. Double click on that to see the output plot. The plot shows the global muon transverse momentum against events.

- to exit ROOT, either, on the GUI click   `file->Quit ROOT`
or, on the root [] prompt, type
```
.q
```

- To exit the container type
```bash
exit
```