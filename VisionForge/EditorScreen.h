#pragma once

#include "Box.h"
#include "Light.h"

#include "Player.h"
#include <InfernoEngine/Camera2D.h>
#include <InfernoEngine/DebugRenderer.h>
#include <InfernoEngine/GLSLProgram.h>
#include <InfernoEngine/GLTexture.h>
#include <InfernoEngine/IGameScreen.h>
#include <InfernoEngine/InputManager.h>
#include <InfernoEngine/SpriteBatch.h>
#include <InfernoEngine/SpriteFont.h>
#include <InfernoEngine/Window.h>
#include <vector>
#include "LevelData.h"

#include <InfernoEngine/GUI.h>

#include "ScreenIndices.h"
#include "ScreenIndices.h"

enum class PhysicsMode {
	RIGID,
	DYNAMIC
};

enum class ObjectMode {
	PLAYER,
	PLATFORM,
	LIGHT,
	FINISH
};

enum class SelectionMode {
	SELECT,
	PLACE
};

const int NO_BOX = -1;
const int NO_LIGHT = -1;

class WidgetLabel {
public:
	WidgetLabel() {};
	WidgetLabel(CEGUI::Window* w, const std::string& text, float scale) :
		widget(w), text(text), scale(scale) {
		// Empty
	};
	void draw(Inferno::SpriteBatch& sb, Inferno::SpriteFont& sf, Inferno::Window* w);

	CEGUI::Window* widget = nullptr;
	std::string text = "";
	Inferno::ColorRGB8 color = Inferno::ColorRGB8(255, 255, 255, 255);
	float scale = 0.7;
};

class EditorScreen : public Inferno::IGameScreen {
public:
	EditorScreen(Inferno::Window* window);
	~EditorScreen();

	/************************************************************************/
	/* IGameScreen Implementation                                           */
	/************************************************************************/
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update() override;
	virtual void draw() override;

private:
	void drawUI();
	void drawWorld();

	void clearLevel();

	void initUI();
	void checkInput();
	void updateMouseDown(const SDL_Event& evnt);
	void updateMouseUp(const SDL_Event& evnt);
	void updateMouseMotion(const SDL_Event& evnt);
	void refreshSelectedBox();
	void refreshSelectedBox(const glm::vec2& newPosition);
	void refreshSelectedLight();
	void refreshSelectedLight(const glm::vec2& newPosition);
	bool isMouseInUI();
	void populateLevelData();

	void setPlatformWidgetVisibility(bool visible);
	void setLightWidgetVisibility(bool visible);

	/************************************************************************/
	/* Event Handlers                                                       */
	/************************************************************************/
	bool onExitClicked(const CEGUI::EventArgs& e);
	bool onColorPickerRedChanged(const CEGUI::EventArgs& e);
	bool onColorPickerGreenChanged(const CEGUI::EventArgs& e);
	bool onColorPickerBlueChanged(const CEGUI::EventArgs& e);
	bool onColorPickerAlphaChanged(const CEGUI::EventArgs& e);
	bool onRigidMouseClick(const CEGUI::EventArgs& e);
	bool onDynamicMouseClick(const CEGUI::EventArgs& e);
	bool onPlayerMouseClick(const CEGUI::EventArgs& e);
	bool onPlatformMouseClick(const CEGUI::EventArgs& e);
	bool onFinishMouseClick(const CEGUI::EventArgs& e);
	bool onLightMouseClick(const CEGUI::EventArgs& e);
	bool onSelectMouseClick(const CEGUI::EventArgs& e);
	bool onPlaceMouseClick(const CEGUI::EventArgs& e);
	bool onSaveMouseClick(const CEGUI::EventArgs& e);
	bool onLoadMouseClick(const CEGUI::EventArgs& e);
	bool onBackMouseClick(const CEGUI::EventArgs& e);
	bool onRotationValueChange(const CEGUI::EventArgs& e);
	bool onSizeValueChange(const CEGUI::EventArgs& e);
	bool onWidthValueChange(const CEGUI::EventArgs& e);
	bool onHeightValueChange(const CEGUI::EventArgs& e);
	bool onDebugToggleClick(const CEGUI::EventArgs& e);
	bool onSaveCancelClick(const CEGUI::EventArgs& e);
	bool onSave(const CEGUI::EventArgs& e);
	bool onLoadCancelClick(const CEGUI::EventArgs& e);
	bool onTestLevelClick(const CEGUI::EventArgs& e);
	bool onLoad(const CEGUI::EventArgs& e);


	/************************************************************************/
	/* Member Variables                                                     */
	/************************************************************************/
	float m_colorPickerRed = 255.0f;
	float m_colorPickerGreen = 255.0f;
	float m_colorPickerBlue = 255.0f;
	float m_colorPickerAlpha = 255.0f;
	float m_rotation = 0.0f;
	float m_lightSize = 10.0f;
	glm::vec2 m_boxDims = glm::vec2(1.0f);
	bool m_mouseButtons[2];
	bool m_debugRender = false;

	CEGUI::GroupBox* m_groupBox = nullptr;
	CEGUI::Slider* m_rSlider = nullptr;
	CEGUI::Slider* m_gSlider = nullptr;
	CEGUI::Slider* m_bSlider = nullptr;
	CEGUI::Slider* m_aSlider = nullptr;
	CEGUI::RadioButton* m_rigidRadioButton = nullptr;
	CEGUI::RadioButton* m_dynamicRadioButton = nullptr;
	CEGUI::RadioButton* m_playerRadioButton = nullptr;
	CEGUI::RadioButton* m_platformRadioButton = nullptr;
	CEGUI::RadioButton* m_finishRadioButton = nullptr;
	CEGUI::RadioButton* m_lightRadioButton = nullptr;
	CEGUI::RadioButton* m_selectRadioButton = nullptr;
	CEGUI::RadioButton* m_placeRadioButton = nullptr;
	CEGUI::ToggleButton* m_debugToggle = nullptr;
	CEGUI::Spinner* m_rotationSpinner = nullptr;
	CEGUI::Spinner* m_widthSpinner = nullptr;
	CEGUI::Spinner* m_heightSpinner = nullptr;
	CEGUI::Spinner* m_sizeSpinner = nullptr;
	CEGUI::FrameWindow* m_saveWindow = nullptr;
	CEGUI::PushButton* m_saveWindowSaveButton = nullptr;
	CEGUI::Combobox* m_saveWindowCombobox = nullptr;
	CEGUI::FrameWindow* m_loadWindow = nullptr;
	CEGUI::PushButton* m_loadWindowLoadButton = nullptr;
	CEGUI::Combobox* m_loadWindowCombobox = nullptr;
	std::vector<CEGUI::ListboxTextItem*> m_saveListBoxItems;
	std::vector<CEGUI::ListboxTextItem*> m_loadListBoxItems;
	CEGUI::PushButton* m_saveButton = nullptr;
	CEGUI::PushButton* m_loadButton = nullptr;
	CEGUI::PushButton* m_backButton = nullptr;
	std::vector<WidgetLabel> m_widgetLabels;

	Inferno::SpriteBatch m_spriteBatch;
	Inferno::SpriteFont m_spriteFont;
	Inferno::GLSLProgram m_textureProgram;
	Inferno::GLSLProgram m_lightProgram;
	Inferno::DebugRenderer m_debugRenderer;

	Inferno::GLTexture m_blankTexture;

	PhysicsMode m_physicsMode = PhysicsMode::RIGID;
	ObjectMode m_objectMode = ObjectMode::PLAYER;
	SelectionMode m_selectMode = SelectionMode::SELECT;

	Inferno::InputManager m_inputManager;

	LevelData levelData;
	bool m_hasPlayer = false;
	Player m_player;
	std::vector<Box> m_boxes;
	std::vector<Light> m_lights;
	int m_selectedBox = NO_BOX;
	int m_selectedLight = NO_LIGHT;
	bool m_isDragging = false;
	glm::vec2 m_selectOffset;

	Inferno::Camera2D m_camera;
	Inferno::Camera2D m_uiCamera;
	Inferno::Window* m_window;
	Inferno::GUI m_gui;
	std::unique_ptr<b2World> m_world;

};