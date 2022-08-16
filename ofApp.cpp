#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetColor(255);

	auto ico_sphere = ofIcoSpherePrimitive(200, 3);
	this->base_mesh = ico_sphere.getMesh();

	this->shader.load("shader/shader.vert", "shader/shader.frag");
	cout << this->base_mesh.getNumVertices(); 
}

//--------------------------------------------------------------
void ofApp::update() {

	this->target_list.clear();
	this->color_list.clear();

	for (auto v : this->base_mesh.getVertices()) {

		for (int i = 0; i < 4; i++) {

			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0025, ofGetFrameNum() * 0.005)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0025, ofGetFrameNum() * 0.005)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0025, ofGetFrameNum() * 0.005)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

			v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
		}

		this->target_list.push_back(v + glm::vec2(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofFill();
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets", &this->target_list[0].x, 1000);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}