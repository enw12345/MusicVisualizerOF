#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	phase = 0;

	int bufferSize = 512;
	sampleRate = 44100;
	phase = 0;
	phaseAdder = 0.0f;
	phaseAdderTarget = 0.0f;
	volume = 0.1f;
	bNoise = false;

	ofSoundStreamSettings settings;
	settings.setOutListener(this);
	settings.sampleRate = sampleRate;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 0;
	settings.bufferSize = bufferSize;

	soundStream.setup(settings);

	soundStream.start();
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ')
	{
		toggleSoundStream = !toggleSoundStream;
		if (toggleSoundStream)
			soundStream.start();
		else
			soundStream.stop();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioOut(ofSoundBuffer& buffer) {
	//cout << "Number of samples: " << buffer.size() << endl;
	
	for (int i = 0; i < buffer.size(); i += 2) {
		float sample = sin(phase); // generating a sine wave sample
		buffer[i] = sample; // writing to the left channel
		buffer[i + 1] = sample; // writing to the right channel
		phase += 0.01;

		cout << sample << endl;
	}
	
}
