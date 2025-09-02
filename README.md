Balancer VST3 Plugin

Version: 1.0
License: GPL-3.0
 

Balancer is a stereo balancing VST3 plugin designed for mixing and mastering. It allows precise control over channel balance and stereo width, helping producers achieve clean, well-defined mixes.

Features

Adjust Left/Right channel balance

Control Stereo Width

Real-time processing with low CPU usage

Smooth parameter automation in DAWs

Intuitive GUI with labeled rotary knobs

Supports standard VST3 hosts (FL Studio, Cubase, Reaper, Ableton Live, etc.)

Screenshots

(Optional: Insert screenshots of the plugin UI, showing channel balance and width controls)

Build Instructions
Requirements

Operating System: Windows 10/11 

IDE: Visual Studio 2022 (Windows)  

JUCE Framework: Version 8 

VST3 SDK: Steinberg VST3 SDK 3.7 or newer

Steps

Clone the repository:

git clone https://github.com/WilliamAshley2019/Balancer.git
cd Balancer


Open Balancer.jucer in Projucer.

Ensure VST3 format is enabled.

Save and export the project for your IDE (Visual Studio / Xcode).

Build the project for your platform.

Copy the generated .vst3 file to your DAW’s plugin folder:

Windows: C:\Program Files\Common Files\VST3\

 
Usage

Load Balancer in your DAW as a VST3 plugin.

Adjust the knobs to control:

Left/Right Balance: Pan audio between channels

Stereo Width: Expand or narrow the stereo image

Automate parameters in your DAW for dynamic stereo effects.

License and Open Source Compliance

Balancer is released under the GNU General Public License v3 (GPL-3.0).

GPL Requirements

Source Code: Must remain open and accessible.

Derivative Works: Must also be licensed under GPL-3.0.

Attribution: Include this README and license file when redistributing.

No Tivoization: You may not impose restrictions preventing modification of the plugin.

The plugin uses:

JUCE Framework (GPLv3 license)

Steinberg VST3 SDK (developers may use it to create and distribute VST3 plugins but may not redistribute the SDK itself)

All project code is compliant with JUCE GPL licensing and the VST3 SDK terms.

Contributing

Contributions are welcome! Fork the repository, make your changes, and submit a pull request. Ensure all modifications comply with GPLv3 licensing.

Contact

Website: https://12264447666william.wixsite.com/williamashley

GitHub: https://github.com/WilliamAshley2019
This vst3 plugin is a basic gain knob plugin that also includes a concept of adding in stereo to mono sum toggle that can be turned on or off so you can not only balance the level but also stereo sum to mono.
It does appear to merge the audio signal and the gain seems to work. 

This was a quick build so I've only tested it once.

To build from source you will need Steinbergs VST3 SDK as well as JUCE etc.. if you are building a project I am guessing you know how to build and compile. 

The source is Open Source GPL3. 

Steinberg (I think owned by Yamaha) developed VST as a virtual studio technology to enbable computers to run software that acted like hardware. They use it as a trademark, which is registered in Europe. 

This project requires JUCE to build from source, and JUCE requires the VST3 SDK to build VST3 plugins. Default plugin basics modules are enough to build this project.

Just drop the vst3 into your commonfiles/vst3 folder and it should work.

This plugin is made for windows 11 as I am a windows user it may work in other versions of windows but hasn't been tested in them.

EULA - Enduser assume all risk in using the vst3 or source code. I have tested it and it works for me, use your own due dilligence in using the vst3, it was made in good faith to provide a simple easy to use no BS gain and stereo to mono sum tool.

This is an alpha.  
 
