//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>




const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec2 texCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	gl_Position = projection * view *  model * vec4(pos, 1.0);\n"
"   TexCoord = texCoord;\n"
"}\n";

const GLchar* ps =
"#version 430\n"
"out vec4 FragColor;\n"
"in vec4 color;\n"
"in vec2 TexCoord;"
"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"void main()\n"
"{\n"
"	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);\n"
"}\n";

using namespace Display;
namespace Example
{

	//------------------------------------------------------------------------------
	/**
	*/
	ExampleApp::ExampleApp()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/
	ExampleApp::~ExampleApp()
	{
		// empty
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool
		ExampleApp::Open()
	{
		App::Open();
		this->window = new Display::Window;
		window->SetKeyPressFunction([this](int32 asciikey, int32 argb, int32 status, int32 mod)
		{
			
		});

		

		GLfloat buf[] =
		{
			-0.5f,	-0.5f,	-1,			// pos 0
			1,		0,		0,		1,	// color 0
			0,		0.5f,	-1,			// pos 1
			0,		1,		0,		1,	// color 0
			0.5f,	-0.5f,	-1,			// pos 2
			0,		0,		1,		1	// color 0
		};
		if (this->window->Open())
		{
			// set clear color to gray
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			
		}
		return true;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		ExampleApp::Run()
	{
		glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);
		//Uncomment the line below if you're not in a VM and then you will have an easier time moving the camera
		//window->SetInputMode(GLFW_CURSOR_DISABLED);

		float radFov = 45 * (PI / 180);

		int width;
		int height;

		this->window->GetSize(width, height);


		stbi_set_flip_vertically_on_load(true);

		Matrix4D projection = projection.perspective(radFov, 800.0f / 600.0f, 0.1f, 100.0f);

		cam.camPos = Vector4D(0.0f, 0.0f, 3.0f);
		cam.camTarget = Vector4D(0.0f, 0.0f, 0.0f);
		cam.camFront = Vector4D(0.0f, 0.0f, -1.0f);
		cam.camUp = Vector4D(0.0f, 1.0f, 0.0f);

		Vector4D lightPosition(-14.2f, 1.0f, 2.0f);

		
		GraphicsNode lightCube;

		std::shared_ptr<MeshResource> pointLightMesh = std::make_shared<MeshResource>();
		std::shared_ptr<TextureResource> lightTexPtr = std::make_shared<TextureResource>();
		std::shared_ptr<ShaderObject> pointLightShader = std::make_shared<ShaderObject>("./resources/LightCubeVS.vs", "./resources/LightCubeFS.fs");


		std::shared_ptr<MeshResource> objectMesh = std::make_shared<MeshResource>();
		std::shared_ptr<ShaderObject> objectShader = std::make_shared<ShaderObject>("./resources/DeferredShadingVS.vs", "./resources/DeferredShadingFS.fs");
		std::shared_ptr<TextureResource> texPtr = std::make_shared<TextureResource>();
		std::shared_ptr<TextureResource> normalMapPtr = std::make_shared<TextureResource>();

		std::shared_ptr<ShaderObject> lightingPassShader = std::make_shared<ShaderObject>("./resources/LightingPassVS.vs", "./resources/LightingPassFS.fs");


		unsigned int gBuffer;
		glGenFramebuffers(1, &gBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
		unsigned int gPosition;
		unsigned int gNormal;
		unsigned int gAlbedo;

		glGenTextures(1, &gPosition);
		glBindTexture(GL_TEXTURE_2D, gPosition);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

		glGenTextures(1, &gNormal);
		glBindTexture(GL_TEXTURE_2D, gNormal);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
		
		glGenTextures(1, &gAlbedo);
		glBindTexture(GL_TEXTURE_2D, gAlbedo);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);

		unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
		glDrawBuffers(3, attachments);

		unsigned int renderBufferDepth;
		glGenRenderbuffers(1, &renderBufferDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBufferDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferDepth);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "FRAMEBUFFER ERROR: Fool, the framebuffer is not complete!" << std::endl;
		}

		float quadBuffer[] = {
		// pos		   // texCoords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};

		unsigned int quadVertexArray;
		unsigned int quadVertexBuffer;
		glGenVertexArrays(1, &quadVertexArray);
		glGenBuffers(1, &quadVertexBuffer);
		glBindVertexArray(quadVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadBuffer), &quadBuffer, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		pointLightMesh->loadObj("./resources/cube2.obj");
		objectMesh->loadGLTF("./resources/Avocado.gltf");

		lightCube.setMesh(pointLightMesh);
		lightCube.setShader(pointLightShader);
		lightCube.setTexture(lightTexPtr);
		//lightCube.initTexture("");
		lightCube.setTransform(Matrix4D());
		lightCube.updateTransform(Matrix4D::scale(Vector4D(10.3, 10.3, 10.3)));


		gn.setMesh(objectMesh);
		gn.setShader(objectShader);
		gn.setTexture(texPtr);
		gn.setNormalMap(normalMapPtr);
		gn.initTexture("./resources/diffuse.jpg");
		gn.setTransform(Matrix4D());

		// gn2.setMesh(objectMesh);
		// gn2.setShader(lightShader);
		// gn2.setTexture(texPtr);s
		// gn2.setTransform(Matrix4D());

		//gn.updateTransform(Matrix4D::scale(Vector4D(0.05, 0.05, 0.05)));

		gn.updateTransform(Matrix4D::scale(Vector4D(10.3, 10.3, 10.3)));
		gn.updateTransform(Matrix4D::roty(160));
		// gn2.updateTransform(Matrix4D::scale(Vector4D(0.3, 0.3, 0.3)));
		// gn2.updateTransform(Matrix4D::translation(Vector4D(2.0f, 2.0f, 2.0f)));


		

		LightNode light = LightNode(lightingPassShader);
		light.setupLighting(lightPosition);

		const int numLights = 20;
		std::vector<Vector4D> lightPositions;
		std::vector<Vector4D> lightColors;
		std::vector<Vector4D> objectPositions;
		
		srand(time(0));

		for (size_t i = 0; i < numLights; i++){
			// float x = ((rand() % 100) / 250.0) * 6.0 - 2.0;
			// float y = ((rand() % 100) / 250.0) * 6.0 - 3.0;
			// float z = ((rand() % 100) / 250.0) * 6.0 - 3.0;
			//objectPositions.push_back(Vector4D(x, y, z));
			
			// these output a value between 0-1
			float r = ((rand() % 255) / 255.0f);
			float g = ((rand() % 255) / 255.0f);
			float b = ((rand() % 255) / 255.0f);
			std::cout << "Color R:" << r << " G:" << g << " B: " << b << "\n";
			lightColors.push_back(Vector4D(r, g, b));
			
			// x = ((rand() % 100) / 10.0) * -6.0 - 2.0;
			// y = ((rand() % 100) / 10.0) * -6.0 - 3.0;
			// z = ((rand() % 100) / 10.0) * -6.0 - 7.0;
			float x = static_cast<float>(((rand() % 100) / 10.0) * 5.0 - 3.0);
			float y = static_cast<float>(((rand() % 100) / 10.0) * 5.0 - 4.0);
			float z = static_cast<float>(((rand() % 100) / 10.0) * 5.0 - 3.0);
			//lightPositions.push_back(Vector4D(x, y, z));
			
		}

		objectPositions.push_back(Vector4D(-3.0, -0.5, -3.0));
		objectPositions.push_back(Vector4D( 0.0, -0.5, -3.0));
		objectPositions.push_back(Vector4D( 3.0, -0.5, -3.0));
		objectPositions.push_back(Vector4D(-3.0, -0.5,  0.0));
		objectPositions.push_back(Vector4D( 0.0, -0.5,  0.0));
		objectPositions.push_back(Vector4D( 3.0, -0.5,  0.0));
		objectPositions.push_back(Vector4D(-3.0, -0.5,  3.0));
		objectPositions.push_back(Vector4D( 0.0, -0.5,  3.0));
		objectPositions.push_back(Vector4D( 3.0, -0.5,  3.0));

		lightPositions.push_back(Vector4D(-4.0, -0.5, -3.0));
		lightPositions.push_back(Vector4D( 0.0, -0.5, -4.0));
		lightPositions.push_back(Vector4D( 3.0, -0.5, -4.0));
		lightPositions.push_back(Vector4D(-4.0, -0.5,  0.0));
		lightPositions.push_back(Vector4D( 0.0, -1.5,  0.0));
		lightPositions.push_back(Vector4D( 4.0, -0.5,  0.0));
		lightPositions.push_back(Vector4D(-4.0, -0.5,  3.0));
		lightPositions.push_back(Vector4D( 0.0, -0.5,  2.0));
		lightPositions.push_back(Vector4D( 3.0, -0.5,  2.0));



		Matrix4D rot;



		std::cout << "width: " << width << " height: " << height << "\n";

		float yaw = -90;
		float pitch = 0;

		float lastX = 512.0f;
		float lastY = 384.0f;
		bool firstRotation = true;
		

		//render loop
		while (this->window->IsOpen())
		{
			//light.lightColor = Vector4D(1.0f, 1.0f, 1.0f);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;	
			lastFrame = currentFrame;

			/*light.intensity = (float)cos(glfwGetTime());
			std::cout << light.intensity << "\n";*/
			
			

			//std::cout << "Lightpos X:" << light.lightPos.x() << " Y:" << light.lightPos.y() << " Z:" << light.lightPos.z() << "\n";

			window->SetKeyPressFunction([this, &light](int32 asciikey, int32 argb, int32 status, int32 mod)
			{
				//std::cout << "asciikey: " << asciikey << " argb: " << argb << " status: " << status << " mod: " << mod << "\n";

				const float camSpeed = 5.0f * deltaTime;

				if (status == 1) {
					switch (asciikey) {
					case GLFW_KEY_W:
						cam.camPos = cam.camPos + cam.camFront * camSpeed;
						break;
					case GLFW_KEY_A:
						cam.camPos = cam.camPos - Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
						break;
					case GLFW_KEY_S:
						cam.camPos = cam.camPos - cam.camFront * camSpeed;
						break;
					case GLFW_KEY_D:
						cam.camPos = cam.camPos + Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
						break;
					case GLFW_KEY_J:
						light.lightPos = light.lightPos - Vector4D(0.5f, 0.0f, 0.0f);
						break;
					case GLFW_KEY_K:
						light.lightPos = light.lightPos + Vector4D(0.0f, 0.0f, 0.5f);
						break;
					case GLFW_KEY_L:
						light.lightPos = light.lightPos + Vector4D(0.5f, 0.0f, 0.0f);
						break;
					case GLFW_KEY_I:
						light.lightPos = light.lightPos + Vector4D(0.0f, 0.0f, -0.5f);
						break;
					case GLFW_KEY_U:
						light.lightPos = light.lightPos + Vector4D(0.0f, -0.5f, 0.0f);
						break;
					case GLFW_KEY_O:
						light.lightPos = light.lightPos + Vector4D(0.0f, 0.5f, 0.0f);
						break;

					case GLFW_KEY_Q:
						cam.camPos = cam.camPos + Vector4D(0.0f, 1.0f, 0.0f) * camSpeed;
						break;
					case GLFW_KEY_E:
						cam.camPos = cam.camPos + Vector4D(0.0f, -1.0f, 0.0f) * camSpeed;
						break;

					}


					
				}
				else if (status == 2) {
					switch (asciikey) {
					case GLFW_KEY_W:
						cam.camPos = cam.camPos + cam.camFront * camSpeed;
						break;
					case GLFW_KEY_A:
						cam.camPos = cam.camPos - Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
						break;
					case GLFW_KEY_S:
						cam.camPos = cam.camPos - cam.camFront * camSpeed;
						break;

					case GLFW_KEY_D:
						cam.camPos = cam.camPos + Vector4D::cross(cam.camFront, cam.camUp).norm() * camSpeed;
						break;
					case GLFW_KEY_J:
						light.lightPos = light.lightPos - Vector4D(0.5f, 0.0f, 0.0f);
						break;
					case GLFW_KEY_K:
						light.lightPos = light.lightPos + Vector4D(0.0f, 0.0f, 0.5f);
						break;
					case GLFW_KEY_L:
						light.lightPos = light.lightPos + Vector4D(0.5f, 0.0f, 0.0f);
						break;
					case GLFW_KEY_I:
						light.lightPos = light.lightPos + Vector4D(0.0f, 0.0f, -0.5f);
						break;
					case GLFW_KEY_U:
						light.lightPos = light.lightPos + Vector4D(0.0f, -0.5f, 0.0f);
						break;
					case GLFW_KEY_O:
						light.lightPos = light.lightPos + Vector4D(0.0f, 0.5f, 0.0f);
						break;

					case GLFW_KEY_Q:
						cam.camPos = cam.camPos + Vector4D(0.0f, 1.0f, 0.0f) * camSpeed;
						break;
					case GLFW_KEY_E:
						cam.camPos = cam.camPos + Vector4D(0.0f, -1.0f, 0.0f) * camSpeed;
						break;
					
					}


				}

				if (asciikey == 256 && status == 1) {
					this->window->Close();
				}
			});
			

			window->SetMousePressFunction([this](int32 mousekey, int32 status, int32 keyc) {
				std::cout << "mousekey: " << mousekey << " status: " << status << " keyc: " << keyc << "\n";
				mousepress = mousekey;
				mousestatus = status;
				});

			window->SetMouseMoveFunction([&](float64 mousex, float64 mousey) {

				if (mousepress == 0 && mousestatus == 1) {


					if (firstRotation) {
						lastX = mousex;
						lastY = mousey;
						firstRotation = false;
					}


					float xoffset = mousex - lastX;
					float yoffset = lastY - mousey; 

					lastX = mousex;
					lastY = mousey;
					const float speed = 0.1f;
					xoffset *= speed;
					yoffset *= speed;

					yaw -= xoffset;
					pitch -= yoffset;
					

					if (pitch > 89.0f) {
						pitch = 89.0f;
					}
					if (pitch < -89.0f) {
						pitch = -89.0f;
					}

					Vector4D direction;
					float degrad = PI / 180;
					direction.x() = -cos(yaw * degrad) * cos(pitch * degrad);
					direction.y() = -sin(pitch * degrad);
					direction.z() = sin(yaw * degrad) * cos(pitch * degrad);

					cam.camFront = direction.norm();

				}
				
				});
			cam.setView();

			//Geometry pass
			glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			objectShader.get()->use();
			objectShader.get()->setMat4(std::string("view"), cam.getView());
			objectShader.get()->setMat4(std::string("projection"), projection);	
			for(size_t i = 0; i < objectPositions.size(); i++){
				Matrix4D model = Matrix4D::translation(objectPositions[i]);
				Matrix4D scale = Matrix4D::scale(Vector4D(10.5f, 10.5f, 10.5f));
				//scale before translation otherwise the lighting will be messed up
				model = scale * model;
				objectShader.get()->setMat4(std::string("model"), model);
				gn.draw(cam, projection, light.lightPos);

			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
			//Lighting pass
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			lightingPassShader.get()->use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, gPosition);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, gNormal);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, gAlbedo);
			for(size_t i = 0; i < lightColors.size(); i++){
				lightingPassShader.get()->setVec3("lights[" + std::to_string(i) + "].position", lightPositions[i]);
				lightingPassShader.get()->setVec3("lights[" + std::to_string(i) + "].color", lightColors[i]);

				const float constant = 1.0f;
				const float linear = 1.7f;
				const float quadratic = 1.8f;
				
				const float maxBrightness = std::fmaxf(std::fmaxf(lightColors[i].x(), lightColors[i].y()), lightColors[i].z());
				const float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
				
				lightingPassShader.get()->setFloat("lights[" + std::to_string(i) + "].linear", linear);
				lightingPassShader.get()->setFloat("lights[" + std::to_string(i) + "].quadratic", quadratic);
				lightingPassShader.get()->setFloat("lights[" + std::to_string(i) + "].radius", radius);

			}
			
			lightingPassShader.get()->setVec3("viewPosition", cam.camPos);
			
			
			//Drawing the screenfilling quad
			glBindVertexArray(quadVertexArray);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);
			
			
			glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			
			glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			pointLightShader.get()->use();
			pointLightShader.get()->setMat4(std::string("view"), cam.getView());
			pointLightShader.get()->setMat4(std::string("projection"), projection);
			for(size_t i = 0; i < lightPositions.size(); i++){
				Matrix4D model = Matrix4D::translation(lightPositions[i]);
				Matrix4D scale = Matrix4D::scale(Vector4D(0.05f, 0.05f, 0.05f));
				// scale before transform
				model = scale * model;
				pointLightShader.get()->setVec3("lightColor", lightColors[i]);
				pointLightShader.get()->setMat4("model", model);
				lightCube.draw(cam, projection, light.lightPos);

			}
			light.updateLighting(cam, projection, lightCube, lightColors[1]);

			//gn2.draw(cam, projection, light.lightPos);
			// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// glActiveTexture(GL_TEXTURE0);
			// glBindTexture(GL_TEXTURE_2D, gPosition);
			// glActiveTexture(GL_TEXTURE1);
			// glBindTexture(GL_TEXTURE_2D, gNormal);
			// glActiveTexture(GL_TEXTURE2);
			// glBindTexture(GL_TEXTURE_2D, gAlbedo);

			///     _             _          __  __ 
			///    | |           | |        / _|/ _|
			///  __| | ___    ___| |_ _   _| |_| |_ 
			/// / _` |/ _ \  / __| __| | | |  _|  _|
			///| (_| | (_) | \__ \ |_| |_| | | | |  
			/// \__,_|\___/  |___/\__|\__,_|_| |_|  
			


			this->window->SwapBuffers();
		}
		gn.clearMemory();
		//gn2.clearMemory();
		glfwTerminate();
	}
}// namespace Example