
#include "Advanced2D.h"

#pragma once

namespace Advanced2D {

    enum RenderType {
        RENDER2D = 0,
        RENDER3D = 1
    };

	enum GAMESTATE {
		MAIN_MENU,
		GAME_PLAY,
		NEXT_SHOT,
		PAUSE,
		SCORING,
		GAME_OVER,
		GAME_STATE_MAX
	};

    class Entity {
    private:
        int id;
        std::string name;
		// flag for whether object is draw to screen or not
        bool visible;
		// flag for physics calculations
        bool awake;
        enum RenderType renderType;
        int objectType;
        int lifetimeLength;
        Timer lifetimeTimer;
		// Store the game state for an object to be draw during
		GAMESTATE drawState;

    public:
        Entity(enum RenderType renderType);
        virtual ~Entity() { };

        virtual void move() = 0;
        virtual void animate() = 0;
        virtual void draw() = 0;

        void setID(int value) { id = value; }
        int getID() { return id; }

        void setRenderType(enum RenderType type) { renderType = type; }
        enum RenderType getRenderType() { return renderType; }

        std::string getName() { return name; }
        void setName(std::string value) { name = value; }

        bool getVisible() { return visible; }
        void setVisible(bool value) { visible = value; }

        bool getAwake() { return awake; }
        void setAwake(bool value) { awake = value; }

        int getLifetime() { return lifetimeLength; }
        void setLifetime(int milliseconds) { lifetimeLength = milliseconds; lifetimeTimer.reset(); }
        bool lifetimeExpired() { return lifetimeTimer.stopwatch(lifetimeLength); }

        int getObjectType() { return objectType; }
        void setObjectType(int value) { objectType = value; }

		void setDrawState(GAMESTATE _drawState) { drawState = _drawState; }
		GAMESTATE getDrawState() { return drawState; }

    };


};
