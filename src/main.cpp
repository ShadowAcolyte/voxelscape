#include <glad/glad.h>
#include <glm/trigonometric.hpp>
#include <sstream>

#include "config.h"
#include "util/log.h"
#include "util/timer.h"
#include "input/input.h"
#include "graphics/window.h"
#include "graphics/camera.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "world/chunk/chunk.h"
#include "world/block/block_atlas.h"
#include "graphics/texture.h"

static Window window;
static Camera cam;

static void _WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    cam.Update(cam.m_fov, width * 1.0f / height, 0.01f, 100.0f);
}

namespace game
{
    static void init()
    {
        Logger::Init();
        Logger::Info("------------------------VOXELSCAPE LOG BEGIN------------------------");
        window.Create();
        glfwSetWindowSizeCallback(window.m_handle, _WindowSizeCallback);
        // Input handling
        Input::InitMouseInput();
        glfwSetCursorPosCallback(window.m_handle, Input::CursorPosCallback);
        glfwSetKeyCallback(window.m_handle, Input::KeyCallback);
        glfwSetInputMode(window.m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        BlockAtlas::Init("textures/texture_atlas.png", "PNG", 16);

        Logger::Info("Initialization complete.");
        Logger::Info("{}", glGetString(GL_VERSION));
    }

    static void run()
    {
        Shader basic("shaders/basic.vert", "shaders/basic.frag", nullptr);
        cam = Camera(glm::radians(Config::FOV), window.m_width * 1.0f / window.m_height, 0.1f, 100.0f);
        Texture texture("textures/arrow_test.jpg", "JPG");

        //int64_t t1, t2; float diff;

        Chunk chunk1(0, 0, 0), chunk2(16, 16, 16), chunk3(16, 16, -16);
        Block dirt(BlockID::DIRT);
        Block grass(BlockID::GRASS);
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                for (int x = 0; x < CHUNK_SIZE; x++) {
                    if ((x * x + y * y + z * z) <= 16 * 16) {
                        chunk1.PlaceBlock(dirt, x, y, z);
                        chunk2.PlaceBlock(dirt, x, y, z);
                        chunk3.PlaceBlock(grass, x, y, z);
                    }
                }
            }
        }
        chunk1.UpdateMesh();
        chunk2.UpdateMesh();
        chunk3.UpdateMesh();

        unsigned int vao, vbo, ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glBindVertexArray(vao);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);
        glfwSwapInterval(0);    // turn off vsync
        std::stringstream _title; _title.setf(std::ios::fixed, std::ios::floatfield); _title.precision(3);
        int64_t _fps_time = 0;
        while (!glfwWindowShouldClose(window.m_handle))
        {
            Input::HandleMouseInput(&cam);
            Input::HandleKeyboardInput(Timer::GetDeltaMs(), &cam);
            cam.Update();

            _fps_time += Timer::GetDeltaNs();
            if (_fps_time > 1000000000) {
                _title << "Voxelscape - FPS: " << Timer::GetFpsAvg() << ", Frame Time : " << Timer::GetDeltaMs() << " ms";
                glfwSetWindowTitle(window.m_handle, _title.str().c_str());
                _title.str("");
                _fps_time = 0;
            }

            //glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            /* Chunk1 */
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * chunk1.m_mesh.m_vertices.size(), &chunk1.m_mesh.m_vertices[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * chunk1.m_mesh.m_indices.size(), &chunk1.m_mesh.m_indices[0], GL_STATIC_DRAW);

            basic.Enable();
            basic.SetViewProj(cam.m_projView);
            glDrawElements(GL_TRIANGLES, chunk1.m_mesh.m_indices.size(), GL_UNSIGNED_INT, 0);
            /* Chunk 2 */
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * chunk2.m_mesh.m_vertices.size(), &chunk2.m_mesh.m_vertices[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * chunk2.m_mesh.m_indices.size(), &chunk2.m_mesh.m_indices[0], GL_STATIC_DRAW);

            basic.Enable();
            basic.SetViewProj(cam.m_projView);
            glDrawElements(GL_TRIANGLES, chunk2.m_mesh.m_indices.size(), GL_UNSIGNED_INT, 0);
            /* Chunk 3 */
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* chunk3.m_mesh.m_vertices.size(), &chunk3.m_mesh.m_vertices[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* chunk3.m_mesh.m_indices.size(), &chunk3.m_mesh.m_indices[0], GL_STATIC_DRAW);

            BlockAtlas::Bind();
            basic.Enable();
            basic.SetViewProj(cam.m_projView);
            glDrawElements(GL_TRIANGLES, chunk3.m_mesh.m_indices.size(), GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 3);
            
            // Swap front and back buffers
            glfwSwapBuffers(window.m_handle);

            // Poll for and process events
            glfwPollEvents();
            Timer::Tick();
        }
    }

    static void destroy()
    {
        window.Destroy();
        Logger::Info("------------------------VOXELSCAPE LOG END------------------------");
    }
}

int main()
{
    game::init();
    game::run();
    game::destroy();
    return 0;
}
