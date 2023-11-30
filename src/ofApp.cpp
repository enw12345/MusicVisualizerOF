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

	//cout << *spectrum << endl;

	light.setAmbientColor(light.getAmbientColor() * *spectrum);
	//light.setDiffuseColor(light.getDiffuseColor() * *spectrum);
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

	//float* spectrum = ofSoundGetSpectrum(1);
	//float spec = *spectrum;

	//glm::vec3 scale = glm::vec3(1, 1 + spec * scaleModify, 1);
	//box.setScale(scale);
	//box.draw();


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

void ofApp::audioOut(ofSoundBuffer& buffer) {
	//cout << "Number of samples: " << buffer.size() << endl;
	
	//for (int i = 0; i < buffer.size(); i += 2) {
	//	float sample = sin(phase); // generating a sine wave sample
	//	buffer[i] = sample; // writing to the left channel
	//	buffer[i + 1] = sample; // writing to the right channel
	//	phase += 0.01;

	//	cout << sample << endl;
	//}


	//for(int i = 0; i < buffer.size(); i += 2)
	//	cout << buffer[i] << " : " << buffer[i + 1] << endl;	
}
