#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableDepthTest();
	ofSetLineWidth(2);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int deg_span = 15;
	float noise_seed_x = ofRandom(300, 1000);
	float noise_seed_y = ofRandom(300, 1000);
	float noise_seed_z = ofRandom(300, 1000);

	ofFill();
	ofDrawSphere(glm::vec3(), 10);
	for (int radius = 30; radius <= 300; radius += 30) {

		ofPushMatrix();
		ofRotateX(ofMap(ofNoise(noise_seed_x - radius * 0.0015 + ofGetFrameNum() * 0.005), 0, 1, -360, 360));
		ofRotateZ(ofMap(ofNoise(noise_seed_y - radius * 0.0015 + ofGetFrameNum() * 0.005), 0, 1, -360, 360));
		ofRotateY(ofMap(ofNoise(noise_seed_z - radius * 0.0015 + ofGetFrameNum() * 0.005), 0, 1, -360, 360));
		for (int deg = 0; deg < 360; deg += deg_span) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5) *DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), 10));
			vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5) *DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), -10));
			vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5) *DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), -10));
			vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5) *DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), 10));

			ofFill();
			ofSetColor(39);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}