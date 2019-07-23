#include <MinGE.h>

#include "Menu.h"
#include "Dice.h"
#include "CameraScript.h"

//#define FULL_SCREEN sf::VideoMode::getDesktopMode()

//#ifdef DEBUG
    #define VIDEOMODE sf::VideoMode(960, 768)
    #define STYLE sf::Style::Default
//#else
//    #define VIDEOMODE FULL_SCREEN
//    #define STYLE sf::Style::Fullscreen
//#endif

void loadTricTrac();

int main()
{
    std::cout << "  -- MinGE --" << std::endl;


    /// Create window
        sf::RenderWindow window(VIDEOMODE, "Tric Trac", STYLE, sf::ContextSettings(24, 0, 0, 4, 3));

    std::cout << window.getSize().x << "  " << window.getSize().y << std::endl;


    /// Create engine
        Engine* engine = new Engine(&window, 60);
        std::cout << "Seed: " << Random::getSeed() << std::endl;

        loadTricTrac();



    /// Main loop
        engine->start();

        while ( Input::isOpen() )
        {
            /// Handle events
                if (Input::getKeyReleased(sf::Keyboard::F1))
                    AABB::drawAABBs = !AABB::drawAABBs;

                if (Input::getKeyReleased(sf::Keyboard::F2))
                    PhysicEngine::get()->setGravity();

                if (Input::getKeyReleased(sf::Keyboard::F3))
                    GraphicEngine::get()->toggleWireframe();



                if (Input::getKeyReleased(sf::Keyboard::Escape))
                    engine->setPause(true);

                if (Input::getMousePressed(sf::Mouse::Left) && Input::hasFocus())
                    engine->setPause(false);

            /// Render
                if (engine->update())
                    window.display();
        }

        std::cout << '\n' << '\n' << std::endl;

    /// Delete resources
        delete engine;

    #ifdef DEBUG
        sf::sleep(sf::seconds(1.0f));
    #endif // DEBUG

    return 0;
}

void loadTricTrac()
{
//    TODO: raycast cylinders

    // Prototypes
        Entity::create("DameNoire", true)
            ->insert<Graphic>(new Model("Models/Dames/dameNoire.obj"))
            ->insert<Piece>()
            ->insert<RigidBody>(0.0f)
//            ->insert<Cylinder>(0.495f, 0.199f);
            ->insert<Box>(vec3(0.5f, 0.5f, 0.2f));

        Entity::create("DameBlanche", true)
            ->insert<Graphic>(new Model("Models/Dames/dameBlanche.obj"))
            ->insert<RigidBody>(0.0f)
            ->insert<Piece>()
//            ->insert<Cylinder>(0.495f, 0.199f);
            ->insert<Box>(vec3(0.5f, 0.5f, 0.2f));

        Entity::create("Jeton", true)
            ->insert<Graphic>(new Model("Models/Dames/jeton.obj"))
            ->insert<RigidBody>(0.0f)
//            ->insert<Cylinder>(0.2f, 0.1f);
            ->insert<Box>(vec3(0.25f, 0.25f, 0.05f));

        Entity::create("Fleche", true)
            ->insert<Graphic>(new Model("Models/Table/fleche.obj"))
            ->insert<Box>(vec3(0.5f, 2.0f, 0.01f), vec3(0, 0.5, 0));

        Entity::create("SlotJeton", true)
            ->insert<Graphic>(Mesh::createCube(Material::base, ALLFLAGS, vec3(0.25f, 0.25f, 0.01f)))
            ->insert<Box>(vec3(0.25f, 0.25f, 0.01f));

        Entity::create("Dice", true)
            ->insert<Graphic>(new Model("Models/Dice/dice2.obj"))
            ->insert<RigidBody>(10.0f)
            ->insert<Box>(vec3(0.05f))
            ->insert<Dice>();


//     Other entities
        Entity::create("Pavillon", false, vec3(-6.525f, 0, 1.0f), vec3(0, 0, PI/2))
            ->insert<Graphic>(new Model("Models/Pavillon/pavillon.obj"))
            ->insert<Box>(vec3(0.6f, 0.1f, 1.0f));

        Entity::create("Tapis", false, vec3(0, 0, -20.0f))
            ->insert<Graphic>(Mesh::createQuad(new ModelMaterial("Tapis", "Textures/tapis.png"), ALLFLAGS, vec2(7.0f, 6.0f)));


        Entity::create("Table", false)
            ->insert<Graphic>(new Model("Models/Table/table.obj"))

            ->insert<RigidBody>(0.0f)

            ->insert<Box>(vec3(6.7f, 5.3f, 0.25f), vec3(0.0, 0, -0.25f)) // Fond

            ->insert<Box>(vec3(6.7f, 0.15f, 0.75f), vec3(0, 5.15f, 0.25f)) // Longueur
            ->insert<Box>(vec3(6.7f, 0.15f, 0.75f), vec3(0, -5.15f, 0.25f)) // Longueur

            ->insert<Box>(vec3(0.15f, 5.3f, 0.75f), vec3(6.5f, 0, 0.25f)) // Largeur
            ->insert<Box>(vec3(0.15f, 5.3f, 0.75f), vec3(-6.5f, 0, 0.25f)) // Largeur

            ->insert<Box>(vec3(0.36f, 5.3f, 0.75f), vec3(0, 0.02f, 0.25f)); // Interieur

        Entity::create("Menu")->insert<Menu>();

    // Light source
        ModelMaterial* bright = new ModelMaterial("bright");
            bright->ambient = vec3(10.0f/4.0f);
            bright->diffuse = vec3(0.0f);
            bright->specular = vec3(0.0f);
            bright->texture = Texture::get("Textures/white.png");

        Entity::create("Light", false, vec3(0, 0, 8))->insert<Light>(GE_POINT_LIGHT, vec3(0.0f), vec3(1.0f), 0.2f, 1.0f, 0.0f, 0.001f);

    // Camera
        Entity::create("MainCamera", false, vec3(0, 0, 10), vec3(0, 0.499f*PI, PI/2))
            ->insert<Camera>(14, 0.1f, 1000.0f, vec3(0.67f, 0.92f, 1.0f), nullptr, true);
}
