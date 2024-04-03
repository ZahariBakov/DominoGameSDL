#include <iostream>
#include <fstream>
#include <sstream>

#include "Game.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "GameConstants.h"

bool Game::Init(const char* title, Vector2D windowPos, int width, int height, uint32_t flags)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
		std::cout << "SDL init success!\n";

        m_window = SDL_CreateWindow(title, windowPos.x, windowPos.y, width, height, flags);
        if(m_window != 0)
        {
			std::cout << "Window creation success!\n";
            m_renderer = SDL_CreateRenderer(m_window, -1, 0);

            if(m_renderer != 0)
            {
				std::cout << "Renderer creation success!\n";
                SDL_SetRenderDrawColor(m_renderer, 64, 64, 64, 255);

                TextureManager::Instance()->LoadTexture("assets/welcome.jpg", "welcome", m_renderer);
                TextureManager::Instance()->LoadTexture("assets/piece.png", "piece", m_renderer);
                TextureManager::Instance()->LoadTexture("assets/free.png", "free", m_renderer);

                m_firstPlayer  = new Player();
                m_secondPlayer = new Player();
                m_table = new Table();
                m_table->SetRenderer(m_renderer);
			}
            else
            {
				std::cout << "Renderer init failed!\n";
				return false;
			}
		}
        else
        {
			std::cout << "Window init failed!\n";
			return false;
		}
	}
    else
    {
		std::cout << "SDL init fail!\n";
		return false;
	}
	std::cout << "Init success!\n";
    m_running = true;

    InitTtf();
    InitSounds();

	return true;
}

bool Game::InitTtf()
{
    if(TTF_Init() == -1)
    {
		return false;
	}

    m_font1 = TTF_OpenFont("fonts/segoepr.ttf", 28);
    m_font2 = TTF_OpenFont("fonts/segoepr.ttf", 72);

    if(m_font1 == nullptr || m_font2 == nullptr)
    {
        std::cout << "Font 1 or Font 2 not load" << std::endl;

		return false;
	}

    /// Create button
    CreateButton("NEW GAME", Vector2D(10, 10), std::bind(&Game::HandleNewGameButtonPressed, this));
    CreateButton("CONTINUE", Vector2D(10, 70), std::bind(&Game::HandleContinueButtonPressed, this));
    CreateButton("CLASSIC", Vector2D(10, 160), std::bind(&Game::HandleClassicButtonPressed, this));
    CreateButton("VEHICLE", Vector2D(140, 160), std::bind(&Game::HandleVehicleButtonPressed, this));
    CreateButton("FLOWER", Vector2D(275, 160), std::bind(&Game::HandleFlowersButtonPressed, this));
    CreateButton("BUTTERFLY", Vector2D(407, 160), std::bind(&Game::HandleButterfliesButtonPressed, this));
    CreateButton("EASY", Vector2D(50, 215), std::bind(&Game::HandleEasyButtonPressed, this));
    CreateButton("NORMAL", Vector2D(140, 215), std::bind(&Game::HandleNormalButtonPressed, this));
    CreateButton("HARD", Vector2D(280, 215), std::bind(&Game::HandleHardButtonPressed, this));
    CreateButton("QUIT", Vector2D(GetWindowsWidth() - 100, GetWindowHeight() - 100), std::bind(&Game::HandleQuitButtonPressed, this));
    CreateButton("RESET SCORE", Vector2D(GetWindowsWidth() - 250, GetWindowHeight() - 400), std::bind(&Game::HandleResetButtonPressed, this));
    CreateButton("WHITE", Vector2D(50, 260), std::bind(&Game::HandleWhiteButtonPressed, this));
    CreateButton("BLACK", Vector2D(155, 260), std::bind(&Game::HandleBlackButtonPressed, this));
    CreateButton("MENU", Vector2D(10, 60), std::bind(&Game::HandleMenuButtonPressed, this));
    CreateButton("PASS", Vector2D(10, 115), std::bind(&Game::HandlePassButtonPressed, this));

    /// Create labels
    CreateLabel(m_font2, "MENU", Vector2D(GetWindowsWidth() / 2 - 100, 40));
    CreateLabel(m_font1, "PLAYER 1", Vector2D(10, GetWindowHeight() - 110));
    CreateLabel(m_font1, "PLAYER 2", Vector2D(10, GetWindowHeight() - 110));
    CreateLabel(m_font1, "SCORE IS RESET",  Vector2D(GetWindowsWidth() - 400, 400));
    CreateLabel(m_font2, "FIRST PLAYER WIN", Vector2D(250, 250));
    CreateLabel(m_font2, "SECOND PLAYER WIN", Vector2D(250, 250));
    CreateLabel(m_font1, "WIN: ", Vector2D(10, GetWindowHeight() - 70));
    CreateLabel(m_font1, "0", Vector2D(90, GetWindowHeight() - 70));
    CreateLabel(m_font1, "1", Vector2D(90, GetWindowHeight() - 70));
    CreateLabel(m_font1, "2", Vector2D(90, GetWindowHeight() - 70));
    CreateLabel(m_font1, "3", Vector2D(90, GetWindowHeight() - 70));
    CreateLabel(m_font1, "4", Vector2D(90, GetWindowHeight() - 70));
    CreateLabel(m_font1, "5", Vector2D(90, GetWindowHeight() - 70));
    CreateLabel(m_font1, "6", Vector2D(90, GetWindowHeight() - 70));
    CreateLabel(m_font1, "7", Vector2D(90, GetWindowHeight() - 70));
    CreateLabel(m_font1, "8", Vector2D(90, GetWindowHeight() - 70));
    CreateLabel(m_font1, "9", Vector2D(90, GetWindowHeight() - 70));

    return true;
}

void Game::InitSounds()
{
    SoundManager::Instance()->Load("assets/sounds/win.wav", "win");
    SoundManager::Instance()->Load("assets/sounds/tap.wav", "tap");
    SoundManager::Instance()->Load("assets/sounds/begin.wav", "begin");
    SoundManager::Instance()->Load("assets/sounds/pass.wav", "pass");
    SoundManager::Instance()->Load("assets/sounds/welcome.wav", "welcome");
}

void Game::Render()
{
    m_timer.HandleEvent();

    SDL_RenderClear(m_renderer);

    if(m_gameFlag > GameFlag::MainMenu)
    {
        for(int row = 0; row < GetMatrixPiecesInRow(); ++row)
        {
            for(int col = 0; col < GetMatrixPiecesInRow(); ++col)
            {
                TextureManager::Instance()->DrawTexture("piece", GetMatrixX() + (row * GetMatrixPieceSize()),
                            GetMatrixY() + (col * GetMatrixPieceSize()), GetMatrixPieceSize(), GetMatrixPieceSize(), m_renderer);
			}
		}

        m_table->Render();

        if(m_playerFlag == PlayerFlag::First)
		{
            m_playerWin = m_firstPlayer->GetWin();

            m_firstPlayer->Render();
		}
        else if(m_playerFlag == PlayerFlag::Second)
        {
            m_playerWin = m_secondPlayer->GetWin();

            m_secondPlayer->Render();
		}
    }

    switch(m_gameFlag)
    {
        case(GameFlag::Welcome):
        {
            SetButtonsVisibility();
            TextureManager::Instance()->DrawTexture("welcome", 0, 0, GetWindowsWidth(), GetWindowHeight(), m_renderer);
            PlaySound("welcome");

            break;
        }
        case(GameFlag::MainMenu):
        {
            if(m_firstPlayer->GetWin() >= GetPlayerMaxWinCount() ||
                m_secondPlayer->GetWin() >= GetPlayerMaxWinCount())
            {
                m_reset = true;
                m_firstPlayer->ResetWin();
                m_secondPlayer->ResetWin();
            }

            SetLabelsVisibility();
            break;
        }
        case(GameFlag::Playing):
        {
            if(m_hasTileForMove)
            {
                m_currentTileForMove.Render();
            }

            SetLabelsVisibility();
            break;
        }
        case(GameFlag::Win):
        {
            SetLabelsVisibility();
            PlaySound("win");
            break;
        }
        default:
        {
            break;
        }
    }

    for(const auto& button : m_buttons)
    {
        button.Render(m_renderer);
    }

    for(const auto& label : m_labels)
    {
        label.Render(m_renderer);
    }

    SDL_SetRenderDrawColor(m_renderer, 64, 64, 64, 255);
    SDL_RenderPresent(m_renderer);  
}

void Game::HandleEvents()
{
	SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                m_running = false;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&m_mouseDownPos.x, &m_mouseDownPos.y);
                    break;
                }

                if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    ShowSelectedTile();
                    m_hasTileForMove = false;
                }
            }
            case SDL_MOUSEBUTTONUP:
            {
                    if(event.button.button != SDL_BUTTON_LEFT)
                    {
                    return;
                    }

                    Vector2D mouseUpPos;
                    SDL_GetMouseState(&mouseUpPos.x, &mouseUpPos.y);

                    HandleTouchEvent(mouseUpPos);

                    break;
            }
            case SDL_MOUSEMOTION:
            {
                int borderOffset = 10;
                if(m_hasTileForMove && m_gameFlag == GameFlag::Playing)
                {
                    m_currentTileForMove.SetPosition(Vector2D(event.motion.x - borderOffset, event.motion.y - borderOffset));
                }
                break;
            }
                case
                SDL_MOUSEWHEEL:
            {
                if(event.wheel.y > 0) // scroll up
                {
                    if(m_hasTileForMove)
                    {
                        UpRotateTile();
                    }
                }
                else if(event.wheel.y < 0) // scroll down
                {
                    if(m_hasTileForMove)
                    {
                        DownRotateTile();
                    }
                }
                break;
            }
            default:
            {
                break;
            }
        }
	}
}

void Game::Deinit()
{
	std::cout << "Cleaning game!\n";

    if(m_gameFlag == GameFlag::Playing)
    {
        WriteDataInFile();
    }

    delete m_firstPlayer;
    delete m_secondPlayer;
    delete m_table;

    TTF_CloseFont(m_font1);
    TTF_CloseFont(m_font2);

    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void Game::HandleTouchEvent(Vector2D mouseUpPos)
{
    for(size_t i = 0; i < m_buttons.size(); ++i)
    {
        m_buttons[i].Unclick();
        m_buttons[i].HandleEvent(m_mouseDownPos, mouseUpPos);
    }

    if(m_gameFlag != GameFlag::Playing)
    {
        return;
    }

    if(m_playerFlag == PlayerFlag::First)
    {
        if(m_firstPlayer->HandleTile(m_mouseDownPos, mouseUpPos, m_table))
        {
            for(size_t i = 0; i < m_firstPlayer->GetPlayerTilesSize(); ++i)
            {
                if(m_firstPlayer->GetTile(i).IsSelected())
                {
                    m_hasTileForMove = true; // has tile for move
                    m_currentTileForMove = m_firstPlayer->GetTile(i);
                    m_firstPlayer->HideTile(i);
                }
            }
        }

        if(m_firstPlayer->AddTileToTable(m_mouseDownPos, mouseUpPos, m_table))
        {
            PlaySound("tap");
            SetButtonsVisibility();
            m_hasTileForMove = false;

            if(CheckForWin())
            {
                m_gameFlag = GameFlag::Win;
                SetButtonsVisibility();
            }
            else
            {
                NextPlayer();
            }
        }
    }
    else if(m_playerFlag == PlayerFlag::Second)
    {
        if(m_secondPlayer->HandleTile(m_mouseDownPos, mouseUpPos, m_table))
        {
            for(size_t i = 0; i < m_secondPlayer->GetPlayerTilesSize(); ++i)
            {
                if(m_secondPlayer->GetTile(i).IsSelected())
                {
                    m_hasTileForMove = true; // has tile for move
                    m_currentTileForMove = m_secondPlayer->GetTile(i);
                    m_secondPlayer->HideTile(i);
                }
            }
        }

        if(m_secondPlayer->AddTileToTable(m_mouseDownPos, mouseUpPos, m_table))
        {
            PlaySound("tap");
            SetButtonsVisibility();
            m_hasTileForMove = false;

            if(CheckForWin())
            {
                m_gameFlag = GameFlag::Win;
                SetButtonsVisibility();
            }
            else
            {
                NextPlayer();
            }
        }
    }
}

bool Game::IsSelected(int idx) const
{
    if(m_playerFlag == PlayerFlag::First)
    {
        m_firstPlayer->UnselectAllTiles();
        m_firstPlayer->SelectCurrentTile(idx);

		return true;
    }
    else if(m_playerFlag == PlayerFlag::Second)
	{
        m_secondPlayer->UnselectAllTiles();
        m_secondPlayer->SelectCurrentTile(idx);

		return true;
	}

	return false;
}

bool Game::IsRunning() const
{
    return m_running;
}

void Game::SetButtonsVisibility()
{
    for(size_t i = 0; i < m_buttons.size(); ++i)
    {
        m_buttons[i].SetVisible(false);
    }

    for(size_t i = 0; i < m_buttons.size(); ++i)
    {
        const auto name = m_buttons[i].GetName();

        if(m_gameFlag == GameFlag::Welcome)
        {
            if(name == "NEW GAME")
            {
                m_buttons[i].SetVisible(true);
            }

            if(IsHaveDataInFile() && name == "CONTINUE")
            {
                m_buttons[i].SetVisible(true);
            }
        }
        else if(m_gameFlag == GameFlag::MainMenu)
        {
            if(name == "CLASSIC" || name == "VEHICLE" || name == "FLOWER" || name == "BUTTERFLY" ||
                name == "QUIT" || name == "RESET SCORE")
            {
                m_buttons[i].SetVisible(true);
            }

            if(m_difficulty == Difficulty::All)
            {
                if(name == "EASY" || name == "NORMAL")
                {
                    m_buttons[i].SetVisible(true);
                }

                if(m_dominoType == DominoType::Classic)
                {
                    if(name == "HARD")
                    {
                        m_buttons[i].SetVisible(true);
                    }
                }
            }

            if(m_difficulty != Difficulty::All && m_difficulty != Difficulty::None && m_dominoType == DominoType::Classic)
            {
                if (name == "WHITE" || name == "BLACK")
                {
                    m_buttons[i].SetVisible(true);
                }
            }
        }
        else if(m_gameFlag == GameFlag::Playing)
        {
            if(name == "PASS" || name == "MENU" ||
                name == "QUIT")
            {
                m_buttons[i].SetVisible(true);
            }

            SetLabelsVisibility();
        }
        else if(m_gameFlag == GameFlag::Win)
        {
            if(name == "MENU" || name == "QUIT")
            {
                m_buttons[i].SetVisible(true);
            }

            SetLabelsVisibility();
        }
    }
}

void Game::SetLabelsVisibility()
{
    for(size_t i = 0; i < m_labels.size(); ++i)
    {
        m_labels[i].SetVisible(false);
    }

    for(size_t i = 0; i < m_labels.size(); ++i)
    {
        const auto name = m_labels[i].GetName();
        const auto winNumber = std::to_string(m_playerWin);

        if(m_gameFlag > GameFlag::MainMenu)
        {
            if(name == "WIN: ")
            {
                m_labels[i].SetVisible(true);
            }

            if(name == winNumber)
            {
                m_labels[i].SetVisible(true);
            }

            if(name == "PLAYER 1" && m_playerFlag == PlayerFlag::First)
            {
                m_labels[i].SetVisible(true);
            }
            else if(name == "PLAYER 2"  && m_playerFlag == PlayerFlag::Second)
            {
                m_labels[i].SetVisible(true);
            }
        }

        if(m_gameFlag == GameFlag::MainMenu)
        {
            if(name == "MENU")
            {
                m_labels[i].SetVisible(true);
            }

            if(m_reset && name == "SCORE IS RESET")
            {
                m_labels[i].SetVisible(true);
            }
        }
        else if(m_gameFlag == GameFlag::Playing)
        {

        }
        else if(m_gameFlag == GameFlag::Win && m_playerFlag == PlayerFlag::First && name == "FIRST PLAYER WIN")
        {
            m_labels[i].SetVisible(true);
        }
        else if(m_gameFlag == GameFlag::Win && m_playerFlag == PlayerFlag::Second && name == "SECOND PLAYER WIN")
        {
            m_labels[i].SetVisible(true);
        }
    }
}

void Game::StartNewGame()
{
    std::cout << "dificulty " << int(m_difficulty) << std::endl;
    std::cout << "tile type  " << int(m_classicTilesType) << std::endl;
	std::string domino;

    switch(m_dominoType)
	{
        case DominoType::Classic:
        {
            std::cout << "domino type is Classic" << std::endl;
            domino = "classic/";
            break;
        }
        case DominoType::Vehicle:
        {
            std::cout << "domino type is Vehicle" << std::endl;
            domino = "vehicle/";
            break;
        }
        case DominoType::Flowers:
        {
            std::cout << "domino type is Flowers" << std::endl;
            domino = "flowers/";
            break;
        }
        case DominoType::Butterflies:
        {
            std::cout << "domino type is Butterflies" << std::endl;
            domino = "butterflies/";
            break;
        }
        case DominoType::None:
        {
            std::cout << "domino type is None" << std::endl;
            break;
        }
        default:
        {
            break;
        }
	}

    m_dominoTiles = new Domino(m_renderer, m_difficulty, m_classicTilesType, domino);
    m_dominoTiles->Shuffle();
    PlaySound("begin");

    if(m_firstPlayer->GetPlayerTilesSize() > 0)
    {
        m_firstPlayer->ClearPlayerTiles();
        m_secondPlayer->ClearPlayerTiles();
        m_table->Clear();
        m_table->CreateMap();
	}

    m_firstPlayer->AddTiles(*m_dominoTiles, m_difficulty);
    std::cout << "First player have tiles" << std::endl;

    m_secondPlayer->AddTiles(*m_dominoTiles, m_difficulty);
    std::cout << "Second player have tiles" << std::endl;

    m_playedTileToWin = m_firstPlayer->GetPlayerTilesSize();
    // m_playedTileToWin = 1;

    Tile tmpTile = m_dominoTiles->GetNextTile();
    m_table->Init(tmpTile);
    std::cout << "Table have tile" << std::endl;
    m_table->ShowAvailablePieces();
    m_playSound = false;

    m_gameFlag = GameFlag::Playing;
    m_timer.Stop();
    SetButtonsVisibility();
}

void Game::NextPlayer()
{
    if(m_playerFlag == PlayerFlag::First)
    {
        m_playerFlag = PlayerFlag::Second;
	}
    else
    {
        m_playerFlag = PlayerFlag::First;
	}
}

void Game::PlaySound(std::string id)
{
    if(!m_playSound)
    {
        m_playSound = true;
        SoundManager::Instance()->PlaySound(id, 0, 0);
	}
}

bool Game::CheckForWin() const
{
    if(m_firstPlayer->GetPlayedTiles() >= m_playedTileToWin && m_playerFlag == PlayerFlag::First)
    {
        m_firstPlayer->AddWin();
		return true;
	}
    else if(m_secondPlayer->GetPlayedTiles() >= m_playedTileToWin && m_playerFlag == PlayerFlag::Second)
    {
        m_secondPlayer->AddWin();
		return true;
	}

    return false;
}

void Game::CreateButton(std::string name, Vector2D buttonPos, std::function<void()> callback)
{
    int tw, th;

    auto tempSurfaceText = TTF_RenderText_Blended(m_font1, name.c_str(), { 255, 255, 255, 255});
    auto btnTex = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);
    SDL_QueryTexture(btnTex, 0, 0, &tw, &th);

    SDL_Rect btnRect = { buttonPos.x, buttonPos.y, tw, th };

    auto button = Button(btnTex, btnRect, name);
    button.SetCallback(callback);
    m_buttons.push_back(button);

    SDL_FreeSurface(tempSurfaceText);
}

void Game::CreateLabel(TTF_Font *font, std::string name, Vector2D labelPos)
{
    Label label;

    auto surfaceText = TTF_RenderText_Blended(font, name.c_str(), { 255, 255, 255, 255 });
    label.SetTexture(SDL_CreateTextureFromSurface(m_renderer, surfaceText));

    Vector2D textureSize;
    SDL_QueryTexture(label.GetTexture(), 0, 0, &textureSize.x, &textureSize.y);
    label.SetRect({ labelPos.x, labelPos.y, textureSize.x, textureSize.y });

    label.SetName(name);

    m_labels.push_back(label);
}

void Game::ShowSelectedTile()
{
    std::cout << "Show tile" << std::endl;

    if(m_playerFlag == PlayerFlag::First)
    {
        for(int i = 0; i < m_firstPlayer->GetPlayerTilesSize(); ++i)
        {
            if(m_firstPlayer->GetTile(i).IsSelected())
            {
                m_firstPlayer->GetTile(i).SetVisible(true);
            }
        }
    }
    else if(m_playerFlag == PlayerFlag::Second)
    {
        for(int i = 0; i < m_secondPlayer->GetPlayerTilesSize(); ++i)
        {
            if(m_secondPlayer->GetTile(i).IsSelected())
            {
                m_secondPlayer->GetTile(i).SetVisible(true);
            }
        }
    }
}

void Game::UpRotateTile()
{
    m_currentTileForMove.UpRotate();

    if(m_playerFlag == PlayerFlag::First)
    {
        for(int i = 0; i < m_firstPlayer->GetPlayerTilesSize(); ++i)
        {
            if(m_firstPlayer->GetTile(i).IsSelected())
            {
                m_firstPlayer->GetTile(i).UpRotate();
            }
        }
    }
    else if(m_playerFlag == PlayerFlag::Second)
    {
        for(int i = 0; i < m_secondPlayer->GetPlayerTilesSize(); ++i)
        {
            if(m_secondPlayer->GetTile(i).IsSelected())
            {
                m_secondPlayer->GetTile(i).UpRotate();
            }
        }
    }
}

void Game::DownRotateTile()
{
    m_currentTileForMove.DownRotate();

    if(m_playerFlag == PlayerFlag::First)
    {
        for(int i = 0; i < m_firstPlayer->GetPlayerTilesSize(); ++i)
        {
            if(m_firstPlayer->GetTile(i).IsSelected())
            {
                m_firstPlayer->GetTile(i).DownRotate();
            }
        }
    }
    else if(m_playerFlag == PlayerFlag::Second)
    {
        for(int i = 0; i < m_secondPlayer->GetPlayerTilesSize(); ++i)
        {
            if(m_secondPlayer->GetTile(i).IsSelected())
            {
                m_secondPlayer->GetTile(i).DownRotate();
            }
        }
    }
}

void Game::HandleNewGameButtonPressed()
{
    if(m_gameFlag != GameFlag::Welcome)
    {
        return;
    }

    std::cout << "NEW GAME Button is clicked!" << std::endl;

    m_gameFlag = GameFlag::MainMenu;
    DeleteDataInFIle();
    SetButtonsVisibility();

    m_timer.Start(10, std::bind(&Game::RunGame, this));
}

void Game::HandleClassicButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu)
    {
        return;
    }

    std::cout << "CLASSIC Button is clicked!" << std::endl;

    m_difficulty = Difficulty::All;
    m_dominoType = DominoType::Classic;
    m_reset = false;
    SetButtonsVisibility();
}

void Game::HandleVehicleButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu)
    {
        return;
    }

    std::cout << "VEHICLE Button is clicked!" << std::endl;

    m_difficulty = Difficulty::All;
    m_dominoType = DominoType::Vehicle;
    m_reset = false;
    SetButtonsVisibility();
}

void Game::HandleFlowersButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu)
    {
        return;
    }

    std::cout << "FLOWERS Button is clicked!" << std::endl;

    m_difficulty = Difficulty::All;
    m_dominoType = DominoType::Flowers;
    m_reset = false;
    SetButtonsVisibility();
}

void Game::HandleButterfliesButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu)
    {
        return;
    }

    std::cout << "BUTTERFLIES Button is clicked!" << std::endl;

    m_difficulty = Difficulty::All;
    m_dominoType = DominoType::Butterflies;
    m_reset = false;
    SetButtonsVisibility();
}

void Game::HandleEasyButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu)
    {
        return;
    }

    std::cout << "EASY buttons is clicked!" << std::endl;

    m_classicTilesType = ClassicTileType::None;
    m_difficulty = Difficulty::Easy;
    m_playSound = false;
    m_reset = false;

    if(m_dominoType == DominoType::Vehicle || m_dominoType == DominoType::Flowers || m_dominoType == DominoType::Butterflies)
    {
        StartNewGame();
    }

    SetButtonsVisibility();
}

void Game::HandleNormalButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu)
    {
        return;
    }

    std::cout << "NORMAL buttons is clicked!" << std::endl;

    m_classicTilesType = ClassicTileType::None;
    m_difficulty = Difficulty::Normal;
    m_playSound = false;
    m_reset = false;

    if(m_dominoType == DominoType::Vehicle || m_dominoType == DominoType::Flowers || m_dominoType == DominoType::Butterflies)
    {
        StartNewGame();
    }

    SetButtonsVisibility();
}

void Game::HandleHardButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu)
    {
        return;
    }

    std::cout << "HARD buttons is clicked!" << std::endl;

    m_difficulty = Difficulty::Hard;
    m_playSound = false;
    m_reset = false;
    SetButtonsVisibility();
}

void Game::HandleQuitButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu && m_gameFlag != GameFlag::Playing && m_gameFlag != GameFlag::Win)
    {
        return;
    }

    std::cout << "QUIT Button is clicked!" << std::endl;

    m_running = false;
}

void Game::HandleResetButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu)
    {
        return;
    }

    std::cout << "RESET SCORE Button is clicked!" << std::endl;

    m_reset = true;
    m_firstPlayer->ResetWin();
    m_secondPlayer->ResetWin();
}

void Game::HandleWhiteButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu)
    {
        return;
    }

    std::cout << "WHITE buttons is clicked!" << std::endl;

    m_classicTilesType = ClassicTileType::White;
    StartNewGame();
    SetButtonsVisibility();
    m_reset = false;
}

void Game::HandleBlackButtonPressed()
{
    if(m_gameFlag != GameFlag::MainMenu)
    {
        return;
    }

    std::cout << "BLACK buttons is clicked!" << std::endl;

    m_classicTilesType = ClassicTileType::Black;;
    StartNewGame();
    SetButtonsVisibility();
    m_reset = false;
}

void Game::HandleMenuButtonPressed()
{
    if(m_gameFlag == GameFlag::Welcome || m_gameFlag == GameFlag::MainMenu || m_buttons[1].IsClicked())
    {
        return;
    }

    std::cout << "MENU Button is clicked!" << std::endl;

    m_dominoType = DominoType::None;
    m_gameFlag = GameFlag::MainMenu;
    SetButtonsVisibility();

    m_firstPlayer->ResetPlayedTiles();
    m_secondPlayer->ResetPlayedTiles();
    m_difficulty = Difficulty::None;   

    m_timer.Start(10, std::bind(&Game::RunGame, this));
}

void Game::HandlePassButtonPressed()
{
    if(m_gameFlag != GameFlag::Playing)
    {
        return;
    }

    std::cout << "PASS Button is clicked! Next player is: " << int(m_playerFlag) << std::endl;

    NextPlayer();
    PlaySound("pass");
    m_playSound = false;
}

void Game::HandleContinueButtonPressed()
{
    if(m_gameFlag != GameFlag::Welcome)
    {
        return;
    }

    std::cout << "CONTINUE Button is clicked." << std::endl;

    m_gameFlag = GameFlag::Playing;

    SetDataFromFile();

    SetButtonsVisibility();
    SetLabelsVisibility();
}

void Game::WriteDataInFile()
{
    std::ofstream gameStateFile;
    gameStateFile.open("GameState.txt");

    const auto gameData = WriteGameData();
    const auto tableData = m_table->WriteTableData();
    const auto firstPlayerData = m_firstPlayer->WritePlayerData();
    const auto secondPlayerData = m_secondPlayer->WritePlayerData();

    const auto allData = gameData + tableData + firstPlayerData + secondPlayerData;

    gameStateFile << allData;

    gameStateFile.close();
}

void Game::DeleteDataInFIle()
{
    std::ofstream gameStateFile("GameState.txt");
    gameStateFile.clear();
}

bool Game::IsHaveDataInFile() const
{
    std::string lineFromGameStateFile;
    std::ifstream gameStateFile("GameState.txt");
    if(getline(gameStateFile, lineFromGameStateFile))
    {
        gameStateFile.close();
        return true;
    }

    return false;
}

std::string Game::WriteGameData() const
{
    std::string data;

    switch(m_playerFlag) {
        case PlayerFlag::First:
        {
            data += "1";
            break;
        }
        case PlayerFlag::Second:
        {
            data += "2";
            break;
        }
        default:
        {
            data += "Unknown";
            break;
        }
    }

    data += " ";

    switch(m_difficulty) {
        case Difficulty::Easy:
        {
            data += "1";
            break;
        }
        case Difficulty::Normal:
        {
            data += "2";
            break;
        }
        case Difficulty::Hard:
        {
            data += "3";
            break;
        }
        default:
        {
            data += "Unknown";
            break;
        }

    }

    data += " ";

    switch (m_dominoType) {
        case DominoType::Vehicle:
        {
            data += "1";
            break;
        }
        case DominoType::Flowers:
        {
            data += "2";
            break;
        }
        case DominoType::Butterflies:
        {
            data += "3";
            break;
        }
        case DominoType::Classic:
        {
            data += "4 ";

            if(m_classicTilesType == ClassicTileType::White)
            {
                data += "1";
            }
            else
            {
                data += "2";
            }

            break;
        }
    default:
            data += "Unknown";
        break;
    }

    data += "\n";

    return data;
}

void Game::ReadDataFromFile()
{
    std::string fileLine;
    std::ifstream dataFile("GameState.txt");

    getline(dataFile, fileLine);
    std::string token;
    std::istringstream gameStream(fileLine);
    while(getline(gameStream, token, ' '))
    {
        m_gameData.push_back(token);
    }

    getline(dataFile, fileLine);
    std::istringstream tableStream(fileLine);
    while(getline(tableStream, token, ' '))
    {
        m_tableData.push_back(token);
    }

    getline(dataFile, fileLine);
    std::istringstream firstPlayerStream(fileLine);
    while(getline(firstPlayerStream, token, ' '))
    {
        m_firstPlayerData.push_back(token);
    }

    getline(dataFile, fileLine);
    std::istringstream secondPlayerStream(fileLine);
    while(getline(secondPlayerStream, token, ' '))
    {
        m_secondPlayerData.push_back(token);
    }

    dataFile.close();
}

void Game::SetDataFromFile()
{
    std::string domino;
    ReadDataFromFile();
    domino = SetGameData();

    m_table->CreateMap();
    m_table->SetTableData(m_tableData);

    m_firstPlayer->SetPlayerData(m_renderer, m_firstPlayerData, m_classicTilesType, domino);
    m_secondPlayer->SetPlayerData(m_renderer, m_secondPlayerData, m_classicTilesType, domino);

    m_playedTileToWin = m_firstPlayer->GetPlayerTilesSize();
    m_gameFlag = GameFlag::Playing;
}

std::string Game::SetGameData()
{
    std::string domino;
    if(m_gameData[0] == "1")
    {
        m_playerFlag = PlayerFlag::First;
    }
    else if(m_gameData[0] == "2")
    {
        m_playerFlag = PlayerFlag::Second;
    }

    if(m_gameData[1] == "1")
    {
        m_difficulty = Difficulty::Easy;
    }
    else if(m_gameData[1] == "2")
    {
        m_difficulty = Difficulty::Normal;
    }
    else if(m_gameData[1] == "3")
    {
        m_difficulty = Difficulty::Hard;
    }

    if(m_gameData[2] == "1")
    {
        m_dominoType = DominoType::Vehicle;
        domino = "vehicle/";
    }
    else if(m_gameData[2] == "2")
    {
        m_dominoType = DominoType::Flowers;
        domino = "flowers/";
    }
    else if(m_gameData[2] == "3")
    {
        m_dominoType = DominoType::Butterflies;
        domino = "butterflies/";
    }
    else if(m_gameData[2] == "4")
    {
        m_dominoType = DominoType::Classic;
        domino = "classic/";

        if(m_gameData[3] == "1")
        {
            m_classicTilesType = ClassicTileType::White;
        }
        else if(m_gameData[3] == "2")
        {
            m_classicTilesType = ClassicTileType::Black;
        }
    }

    return domino;
}

void Game::RunGame()
{
    std::cout << "RunGame..." << std::endl;

    m_dominoType = DominoType::Classic;
    m_difficulty = Difficulty::Easy;
    StartNewGame();
}
