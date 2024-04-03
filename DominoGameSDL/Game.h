#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Domino.h"
#include "Player.h"
#include "Table.h"
#include "Tools/Button.h"
#include "Enums.h"
#include "Tools/Vector2D.h"
#include "Tools/Label.h"
#include "Tools/Timer.h"

class Game
{
public:
    Game() {};
    ~Game() {};

    auto Init(const char* title, Vector2D windowPos, int width, int height, uint32_t flags) -> bool;
    auto InitTtf() -> bool;

    void InitSounds();
    void PlaySound(std::string id);

    void Deinit();

    void Render();

    void HandleEvents();
    void HandleTouchEvent(Vector2D mouseUpPos);

    auto IsSelected(int idx) const -> bool;
    auto IsRunning() const -> bool;

    void SetButtonsVisibility();

    void SetLabelsVisibility();
	
private:   
    void HandleNewGameButtonPressed();
    void HandleClassicButtonPressed();
    void HandleVehicleButtonPressed();
    void HandleFlowersButtonPressed();
    void HandleButterfliesButtonPressed();
    void HandleEasyButtonPressed();
    void HandleNormalButtonPressed();
    void HandleHardButtonPressed();
    void HandleQuitButtonPressed();
    void HandleResetButtonPressed();
    void HandleWhiteButtonPressed();
    void HandleBlackButtonPressed();
    void HandleMenuButtonPressed();
    void HandlePassButtonPressed();
    void HandleContinueButtonPressed();

    void WriteDataInFile();
    void DeleteDataInFIle();
    auto IsHaveDataInFile() const -> bool;

    auto WriteGameData() const -> std::string;
    void ReadDataFromFile();
    void SetDataFromFile();
    auto SetGameData() -> std::string;

    void HandleTimerCallback(std::function<void()> callback);
    void RunGame();

    void StartNewGame();
    void NextPlayer();

    auto CheckForWin() const -> bool;

    void CreateButton(std::string name, Vector2D buttonPos, std::function<void()> callback);

    void CreateLabel(TTF_Font* font, std::string name, Vector2D pos);

    void ShowSelectedTile();

    void UpRotateTile();
    void DownRotateTile();

    SDL_Window* m_window     = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    bool m_running     = true;
    bool m_isInMatrix  = false;
    bool m_playSound   = false;
    bool m_reset       = false;
    bool m_hasTileForMove = false;

    Tile m_currentTileForMove;

    Vector2D m_mouseDownPos;

    int m_playedTileToWin = 1;
    int m_tileIdx         = 0;
    int m_playerWin       = 0;

    Player* m_firstPlayer;
    Player* m_secondPlayer;
    Table*  m_table;
    Domino* m_dominoTiles;

    TTF_Font* m_font1 {};
    TTF_Font* m_font2 {};

    PlayerFlag m_playerFlag            = PlayerFlag::First;
    Difficulty m_difficulty            = Difficulty::None;
    DominoType m_dominoType            = DominoType::Classic;
    GameFlag   m_gameFlag              = GameFlag::Welcome;
    ClassicTileType m_classicTilesType = ClassicTileType::White;

    std::vector<Button> m_buttons;
    std::vector<Label>  m_labels;
    std::vector<std::string> m_gameData;
    std::vector<std::string> m_tableData;
    std::vector<std::string> m_firstPlayerData;
    std::vector<std::string> m_secondPlayerData;
    Timer m_timer;
};
