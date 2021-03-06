import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: "../../.."

    ofApp {
        name: { return FileInfo.baseName(path) }

        files: [
            "src/Effects/PerlinNoiseEffect.cpp",
            "src/Effects/PerlinNoiseEffect.h",
            'src/Animations.cpp',
            'src/Animations.h',
            'src/Circuit.cpp',
            'src/Circuit.h',
            'src/Effects/BaseEffect.cpp',
            'src/Effects/BaseEffect.h',
            'src/Effects/BloomEffect.cpp',
            'src/Effects/BloomEffect.h',
            'src/Effects/CalibrateEffect.cpp',
            'src/Effects/CalibrateEffect.h',
            'src/Effects/EmptyEffect.cpp',
            'src/Effects/EmptyEffect.h',
            'src/Effects/ImagePan.cpp',
            'src/Effects/ImagePan.h',
            'src/Effects/LineEffect.cpp',
            'src/Effects/LineEffect.h',
            'src/Effects/LineEffect2.cpp',
            'src/Effects/LineEffect2.h',
            'src/Effects/NoiseEffect.cpp',
            'src/Effects/NoiseEffect.h',
            'src/Effects/NoiseParticlesEffect.cpp',
            'src/Effects/NoiseParticlesEffect.h',
            'src/Effects/TrailParticles.cpp',
            'src/Effects/TrailParticles.h',
            'src/GuiMap.cpp',
            'src/GuiMap.h',
            'src/LedFixture.cpp',
            'src/LedFixture.h',
            'src/LedPixel.cpp',
            'src/LedPixel.h',
            'src/LightsEditor.cpp',
            'src/LightsEditor.h',
            'src/Tree.cpp',
            'src/Tree.h',
            'src/TreeData.cpp',
            'src/TreeData.h',
            'src/main.cpp',
            'src/ofApp.cpp',
            'src/ofApp.h',
        ]

        of.addons: [
            'ofxArtnet',
            'ofxDatGui',
            'ofxGenericDmx',
            'ofxMarkovChain',
            'ofxOsc',
            'ofxPlaylist',
            'ofxXmlSettings',
            'ofxThreadedImageLoader',
            'ofxPoco',
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
                                // and can be checked with #ifdef or #if in the code

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'
	
		cpp.dynamicLibraries: ["ftdi1"]


        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
