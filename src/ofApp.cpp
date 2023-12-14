#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//Get and play an audio clip
	player = ofSoundPlayer();
	player.load("music/Arcanum.mp3");
	player.play();
	player.setLoop(true);

	//Draw something visualizing the audio
	light.setup();
	light.setPosition(-100, 200, 0);
	ofEnableDepthTest();
	
	boxMaterial.setDiffuseColor(ofFloatColor::red);
	boxMaterial.setShininess(0.02);

	for (int i = 0; i < barAmount - 1; i++) {
		bars[i] = ofBoxPrimitive();

		float x = bars[i].getPosition().x - barAmount * 25;

		glm::vec3 position = glm::vec3(i * barAmount + x, 0, 0);
		bars[i].setPosition(position);
	}

	float zoom = cam.getGlobalPosition().z + 4000;
	cam.setPosition(cam.getGlobalPosition().x, cam.getGlobalPosition().y, zoom);
	
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
	float* spectrum = ofSoundGetSpectrum(512);

	light.setAmbientColor(light.getAmbientColor() * *spectrum);
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	boxMaterial.begin();

	for (int i = 0; i < barAmount - 1; i++) {

		float* spectrum = ofSoundGetSpectrum(i + 1);
		float spec = *spectrum;

		
		glm::vec3 scale = glm::vec3(.1f, .1f + spec * scaleModify, .1f);
		bars[i].setScale(scale);

		bars[i].draw();
	}

	boxMaterial.end();

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ')
	{
		toggleSoundStream = !toggleSoundStream;
		if (toggleSoundStream) {
			player.play();
			soundStream.start();
			cout << "PLAY" << endl;
		}
		else {
			player.stop();
			soundStream.stop();
			cout << "PAUSE" << endl;
		}
	}

	cout << cam.getGlobalPosition() << endl;
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
