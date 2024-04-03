#include <iostream>

#include "Table.h"
#include "Tile.h"
#include "GameConstants.h"

Table::Table()
{
    CreateMap();
}

void Table::Init(Tile tile)
{
    m_firstFreeValue  = tile.GetFirst();
    m_secondFreeValue = tile.GetSecond();

    auto GetCenterPos = GetCenterTablePos();

    // Placing the first tile in the center of the table
    m_tableBox[GetCenterPos.y][GetCenterPos.x].SetValue(tile.GetFirst());
    m_tableBox[GetCenterPos.y][GetCenterPos.x + 1].SetValue(tile.GetSecond());

    m_firstFreePos.x  = GetCenterPos.x;
    m_firstFreePos.y  = GetCenterPos.y;
    m_secondFreePos.x = GetCenterPos.x + 1;
    m_secondFreePos.y = GetCenterPos.y;

    // m_tableTile[GetCenterPos.y][GetCenterPos.x].SetValues(tile.GetFirst(), tile.GetSecond());
}

void Table::AddTile(Tile newTile, Vector2D tilePos)
{
    auto firstBox  = newTile.GetFirst();
    auto secondBox = newTile.GetSecond();

    if(newTile.IsHorizontal())
    {
        m_tableBox[tilePos.y][tilePos.x].SetValue(firstBox);
        m_tableBox[tilePos.y][tilePos.x + 1].SetValue(secondBox);
    }
    else if(!newTile.IsHorizontal())
    {
        m_tableBox[tilePos.y][tilePos.x].SetValue(firstBox);
        m_tableBox[tilePos.y + 1][tilePos.x].SetValue(secondBox);
    }

    ShowAvailablePieces();

    std::cout << "First free - Second free: " << m_firstFreeValue << "-" << m_secondFreeValue << std::endl;
    std::cout << "First free pos: " << m_firstFreePos.x << "-" << m_firstFreePos.y << std::endl;
    std::cout << "Second free pos: " << m_secondFreePos.x << "-" << m_secondFreePos.y << std::endl;
}

void Table::ShowAvailablePieces()
{
    auto currentLeftValue  = m_tableBox[m_firstFreePos.y][m_firstFreePos.x].GetValue();
    auto currentRightValue = m_tableBox[m_secondFreePos.y][m_secondFreePos.x].GetValue();

    HideOldAvailablePieces();

    ShowAvailableFirstFreePieces();
    ShowAvailableSecondPieces();
}

void Table::ShowAvailableFirstFreePieces()
{
    const auto firstFreeXPos = m_firstFreePos.x;
    const auto firstFreeYPos = m_firstFreePos.y;

    if( firstFreeXPos > 0)
    {
        auto& firstFreeLeft  = m_tableBox[firstFreeYPos][firstFreeXPos - 1];
        if(firstFreeLeft.GetValue() == "*")
        {
            firstFreeLeft.SetValue("free");
        }
    }

    if(firstFreeXPos < GetPenultimateMatrixPiece())
    {
        auto& firstFreeRight = m_tableBox[firstFreeYPos][firstFreeXPos + 1];
        if(firstFreeRight.GetValue() == "*" )
        {
            firstFreeRight.SetValue("free");
        }
    }

    if(firstFreeYPos < GetPenultimateMatrixPiece())
    {
        auto& firstFreeDown  = m_tableBox[firstFreeYPos + 1][firstFreeXPos];
        if(firstFreeDown.GetValue() == "*")
        {
            firstFreeDown.SetValue("free");
        }
    }

    if(firstFreeYPos > 0)
    {
        auto& firstFreeUp    = m_tableBox[firstFreeYPos - 1][firstFreeXPos];
        if(firstFreeUp.GetValue() == "*")
        {
           firstFreeUp.SetValue("free");
        }
    }
}

void Table::ShowAvailableSecondPieces()
{
    const auto secondFreeXPos = m_secondFreePos.x;
    const auto secondFreeYPos = m_secondFreePos.y;
    const auto secondMatrixPiece = 1;

    if(secondFreeXPos > secondMatrixPiece)
    {
        auto& secondFreeLeft  = m_tableBox[secondFreeYPos][secondFreeXPos - 1];
        if(secondFreeLeft.GetValue() == "*")
        {
            secondFreeLeft.SetValue("free");
        }
    }

    if(secondFreeXPos < GetPenultimateMatrixPiece())
    {
        auto& secondFreeRight = m_tableBox[secondFreeYPos][secondFreeXPos + 1];
        if(secondFreeRight.GetValue() == "*")
        {
            secondFreeRight.SetValue("free");
        }
    }

    if(secondFreeYPos < GetPenultimateMatrixPiece())
    {
        auto& secondFreeDown  = m_tableBox[secondFreeYPos + 1][secondFreeXPos];
        if(secondFreeDown.GetValue() == "*")
        {
            secondFreeDown.SetValue("free");
        }
    }

    if(secondFreeYPos > secondMatrixPiece)
    {
        auto& secondFreeUp    = m_tableBox[secondFreeYPos - 1][secondFreeXPos];
        if(secondFreeUp.GetValue() == "*")
        {
            secondFreeUp.SetValue("free");
        }
    }
}

void Table::HideOldAvailablePieces()
{
    for(int row = 0; row < TABLE_SIZE; ++row)
    {
        for(int col = 0; col < TABLE_SIZE; ++col)
        {
            if(m_tableBox[row][col].GetValue() == "free")
            {
                m_tableBox[row][col].SetValue("*");
            }
        }
    }
}

bool Table::CheckForPlacement(Tile playerTile, Vector2D posDown, Vector2D posUp)
{
    // Press and Unpress pieces
    const auto xPress   = (posDown.x - GetMatrixX()) / GetMatrixPieceSize();
    const auto yPress   = (posDown.y - GetMatrixY()) / GetMatrixPieceSize();
    const auto xUnpress = (posUp.x - GetMatrixX())   / GetMatrixPieceSize();
    const auto yUnpress = (posUp.y - GetMatrixY())   / GetMatrixPieceSize();

	std::cout << "xDown-yDown " << xPress << "-" << yPress << std::endl;

    // All needed positions
    auto leftBoxPos         = Vector2D{ xPress, yPress };
    auto rightBoxPos        = Vector2D{ xPress, yPress };
    auto upBoxPos           = Vector2D{ xPress, yPress };
    auto upAndRightBoxPos   = Vector2D{ xPress, yPress };
    auto doubleRightBoxPos  = Vector2D{ xPress, yPress };
    auto downBoxPos         = Vector2D{ xPress, yPress };
    auto downAndLeftBoxPos  = Vector2D{ xPress, yPress };
    auto downAndRightBoxPos = Vector2D{ xPress, yPress };
    auto doubleDownBoxPos   = Vector2D{ xPress, yPress };

    // Update positions
    if(xPress > 0)
    {
        leftBoxPos.x -= 1;
    }

    if(xPress < GetPenultimateMatrixPiece())
    {
        rightBoxPos.x += 1;
    }

    if(yPress > 0)
    {
        upBoxPos.y -= 1;

        if(xPress < GetPenultimateMatrixPiece())
        {
            upAndRightBoxPos.x += 1;
            upAndRightBoxPos.y -= 1;
        }
    }

    if(xPress < GetPenultimateMatrixPiece() - 1)
    {
        doubleRightBoxPos.x += 2;
    }

    if(yPress < GetPenultimateMatrixPiece())
    {
        downBoxPos.y += 1;

        if(xPress > 0)
        {
            downAndLeftBoxPos.x -= 1;
            downAndLeftBoxPos.y += 1;
        }

        if(xPress < GetPenultimateMatrixPiece())
        {
            downAndRightBoxPos.x += 1;
            downAndRightBoxPos.y += 1;
        }
    }

    if(yPress < GetPenultimateMatrixPiece() - 1)
    {
        doubleDownBoxPos.y += 2;
    }

    // auto leftBoxPos         = Vector2D{ xPress - 1, yPress };
    // auto rightBoxPos        = Vector2D{ xPress + 1, yPress };
    // auto upBoxPos           = Vector2D{ xPress, yPress - 1 };
    // auto upAndRightBoxPos   = Vector2D{ xPress + 1, yPress - 1 };
    // auto doubleRightBoxPos  = Vector2D{ xPress + 2, yPress };
    // auto downBoxPos         = Vector2D{ xPress, yPress + 1 };
    // auto downAndLeftBoxPos  = Vector2D{ xPress - 1, yPress + 1 };
    // auto downAndRightBoxPos = Vector2D{ xPress + 1, yPress + 1 };
    // auto doubleDownBoxPos   = Vector2D{ xPress, yPress + 2 };

    // std::cout << "Left box pos x-y: "           << leftBoxPos.x         << "-" << leftBoxPos.y         << std::endl;
    // std::cout << "Right box pos x-y: "          << rightBoxPos.x        << "-" << rightBoxPos.y        << std::endl;
    // std::cout << "Up box pos x-y: "             << upBoxPos.x           << "-" << upBoxPos.y           << std::endl;
    // std::cout << "Up and Right box pos x-y: "   << upAndRightBoxPos.x   << "-" << upAndRightBoxPos.y   << std::endl;
    // std::cout << "Double Right box pos x-y: "   << doubleRightBoxPos.x  << "-" << doubleRightBoxPos.y  << std::endl;
    // std::cout << "Down box pos x-y: "           << downBoxPos.x         << "-" << downBoxPos.y         << std::endl;
    // std::cout << "Down and left box pos x-y: "  << downAndLeftBoxPos.x  << "-" << downAndLeftBoxPos.y  << std::endl;
    // std::cout << "Down and Right box pos x-y: " << downAndRightBoxPos.x << "-" << downAndRightBoxPos.y << std::endl;
    // std::cout << "Double Down box pos x-y: "    << doubleDownBoxPos.x   << "-" << doubleDownBoxPos.y   << std::endl;

    // All needed boxes
    const auto& currentBox      = m_tableBox[yPress][xPress];
    const auto& rightBox        = m_tableBox[rightBoxPos.y][rightBoxPos.x];
    const auto& leftBox         = m_tableBox[leftBoxPos.y][leftBoxPos.x];
    const auto& upBox           = m_tableBox[upBoxPos.y][upBoxPos.x];
    const auto& upAndRightBox   = m_tableBox[upAndRightBoxPos.y][upAndRightBoxPos.x];
    const auto& downBox         = m_tableBox[downBoxPos.y][downBoxPos.x];
    const auto& downAndRightBox = m_tableBox[downAndRightBoxPos.y][downAndRightBoxPos.x];
    const auto& downAndLeftBox  = m_tableBox[downAndLeftBoxPos.y][downAndLeftBoxPos.x];
    const auto& doubleRightBox  = m_tableBox[doubleRightBoxPos.y][doubleRightBoxPos.x];
    const auto& doubleDownBox   = m_tableBox[doubleDownBoxPos.y][doubleDownBoxPos.x];

    // std::cout << "Current box value: "        << currentBox.GetValue()      << std::endl;
    // std::cout << "Right box value: "          << rightBox.GetValue()        << std::endl;
    // std::cout << "Left box value: "           << leftBox.GetValue()         << std::endl;
    // std::cout << "Up box value: "             << upBox.GetValue()           << std::endl;
    // std::cout << "Down box value: "           << downBox.GetValue()         << std::endl;
    // std::cout << "Up and Right box value: "   << upAndRightBox.GetValue()   << std::endl;
    // std::cout << "Down and Right box value: " << downAndRightBox.GetValue() << std::endl;
    // std::cout << "Down and left box value: "  << downAndLeftBox.GetValue()  << std::endl;
    // std::cout << "Double Right box value: "   << doubleRightBox.GetValue()  << std::endl;
    // std::cout << "Double Down box value: "    << doubleDownBox.GetValue()   << std::endl;

    // Early Return
    if((xPress != xUnpress) || (yPress != yUnpress))
	{
        std::cout << "Current box value: " << currentBox.GetValue() << std::endl;

        std::cout << "Player click in different pices!" << std::endl;
        return false;
	}

    if(!(currentBox.GetValue() == "*" || currentBox.GetValue() == "free") && !(rightBox.GetValue()== "*" || rightBox.GetValue() == "free")
        && playerTile.IsHorizontal())
    {
        std::cout << "Current piece is already used!" << std::endl;
        return false;
    }

    if(!(currentBox.GetValue() == "*" || currentBox.GetValue() == "free") && !(downBox.GetValue()== "*" || downBox.GetValue() == "free")
        && !playerTile.IsHorizontal())
    {
        std::cout << "Current piece is already used!" << std::endl;
        return false;
    }

    if((playerTile.GetFirst() != m_firstFreeValue) && (playerTile.GetFirst() != m_secondFreeValue) &&
        (playerTile.GetSecond() != m_firstFreeValue) && (playerTile.GetSecond() != m_secondFreeValue))
    {
        std::cout << "Player tile first - second " << playerTile.GetFirst() << "-" << playerTile.GetSecond() << std::endl;
        std::cout << "First free - Second free: " << m_firstFreeValue << "-" << m_secondFreeValue << std::endl;
        std::cout << "This tile no match with first free or second free." << std::endl;
        return false;
    }

    // Checks
    if(playerTile.IsHorizontal() && (xPress < GetMatrixPiecesInRow() - 1))
    {
        if(playerTile.GetFirst() == m_firstFreeValue &&
            CheckTileFirstWithFirstFree(CheckTileData(playerTile, leftBox, downBox, upBox, leftBoxPos, downBoxPos, upBoxPos)) &&
            rightBox.GetValue()== "*")
        {
            std::cout << "Add tile. First tile box = First free." << std::endl;

            m_firstFreeValue = playerTile.GetSecond();
            m_firstFreePos.x = xPress + 1;
            m_firstFreePos.y = yPress;

            AddTile(playerTile, Vector2D { xPress, yPress });
            return true;
        }

        if(playerTile.GetFirst() == m_secondFreeValue &&
            CheckTileFirstWithSecondFree(CheckTileData(playerTile, leftBox, downBox, upBox, leftBoxPos, downBoxPos, upBoxPos)) &&
            rightBox.GetValue()== "*")
        {
            std::cout << "Add tile. First tile box = Second free." << std::endl;

            m_secondFreeValue = playerTile.GetSecond();
            m_secondFreePos.x = xPress + 1;
            m_secondFreePos.y = yPress;

            AddTile(playerTile, Vector2D { xPress, yPress });
            return true;
        }

        if(playerTile.GetSecond() == m_firstFreeValue &&
            CheckTileSecondWithFirstFree(CheckTileData(playerTile, upAndRightBox, downAndRightBox, doubleRightBox, upAndRightBoxPos, downAndRightBoxPos, doubleRightBoxPos)) &&
            currentBox.GetValue()== "*")
        {
            SecondTileMatchWithFirstFree(playerTile, xPress, yPress);
            return true;
        }

        if(playerTile.GetSecond() == m_secondFreeValue &&
            CheckTileSecondWithSecondFree(CheckTileData(playerTile, upAndRightBox, downAndRightBox, doubleRightBox, upAndRightBoxPos, downAndRightBoxPos, doubleRightBoxPos)) &&
            currentBox.GetValue()== "*")
        {
            SecondTileMatchWithSecondFree(playerTile, xPress, yPress);
            return true;
        }
    }
    else if(!playerTile.IsHorizontal())
    {
        if(playerTile.GetFirst() == m_firstFreeValue &&
            CheckTileFirstWithFirstFree(CheckTileData(playerTile, leftBox, rightBox, upBox, leftBoxPos, rightBoxPos, upBoxPos)) &&
            downBox.GetValue() == "*")
        {
            std::cout << "Add tile. First tile box = First free." << std::endl;

            m_firstFreeValue = playerTile.GetSecond();
            m_firstFreePos.x = xPress;
            m_firstFreePos.y = yPress + 1;

            AddTile(playerTile, Vector2D { xPress, yPress });
            return true;
        }

        if(playerTile.GetFirst() == m_secondFreeValue &&
            CheckTileFirstWithSecondFree(CheckTileData(playerTile, leftBox, rightBox, upBox, leftBoxPos, rightBoxPos, upBoxPos)) &&
            downBox.GetValue() == "*")
        {
            std::cout << "Add tile. First tile box = Second free." << std::endl;

            m_secondFreeValue = playerTile.GetSecond();
            m_secondFreePos.x = xPress;
            m_secondFreePos.y = yPress + 1;

            AddTile(playerTile, Vector2D { xPress, yPress });
            return true;
        }

        if(playerTile.GetSecond() == m_firstFreeValue &&
            CheckTileSecondWithFirstFree(CheckTileData(playerTile, downAndLeftBox, downAndRightBox, doubleDownBox, downAndLeftBoxPos, downAndRightBoxPos, doubleDownBoxPos)) &&
            currentBox.GetValue() == "*")
        {
            SecondTileMatchWithFirstFree(playerTile, xPress, yPress);
            return true;
        }

        if(playerTile.GetSecond() == m_secondFreeValue &&
            CheckTileSecondWithSecondFree(CheckTileData(playerTile, downAndLeftBox, downAndRightBox, doubleDownBox, downAndLeftBoxPos, downAndRightBoxPos, doubleDownBoxPos)) &&
            upBox.GetValue() == "*")
        {
            SecondTileMatchWithSecondFree(playerTile, xPress, yPress);
            return true;
        }
    }

    std::cout << "Player tile first - second " << playerTile.GetFirst() << "-" << playerTile.GetSecond()
              << " is " << playerTile.IsHorizontal() << std::endl;
    return false;
}

bool Table::CheckTileFirstWithFirstFree(CheckTileData checkTileData) const
{
    if(
        (checkTileData.firstBox.GetValue()  == checkTileData.playerTile.GetFirst() && checkTileData.firstBoxPos == m_firstFreePos)  ||
        (checkTileData.secondBox.GetValue() == checkTileData.playerTile.GetFirst() && checkTileData.secondBoxPos == m_firstFreePos) ||
        (checkTileData.thirdBox.GetValue()  == checkTileData.playerTile.GetFirst() && checkTileData.thirdBoxPos == m_firstFreePos)
        )
    {
        return true;
    }

    return false;
}

bool Table::CheckTileFirstWithSecondFree(CheckTileData checkTileData) const
{
    if(
        (checkTileData.firstBox.GetValue()  == checkTileData.playerTile.GetFirst() && checkTileData.firstBoxPos == m_secondFreePos)  ||
        (checkTileData.secondBox.GetValue() == checkTileData.playerTile.GetFirst() && checkTileData.secondBoxPos == m_secondFreePos) ||
        (checkTileData.thirdBox.GetValue()  == checkTileData.playerTile.GetFirst() && checkTileData.thirdBoxPos == m_secondFreePos)
        )
    {
        return true;
    }

    return false;
}

bool Table::CheckTileSecondWithFirstFree(CheckTileData checkTileData) const
{
    if(
        (checkTileData.firstBox.GetValue()  == checkTileData.playerTile.GetSecond() && checkTileData.firstBoxPos == m_firstFreePos)  ||
        (checkTileData.secondBox.GetValue() == checkTileData.playerTile.GetSecond() && checkTileData.secondBoxPos == m_firstFreePos) ||
        (checkTileData.thirdBox.GetValue()  == checkTileData.playerTile.GetSecond() && checkTileData.thirdBoxPos == m_firstFreePos)
        )
    {
        return true;
    }

    return false;
}

bool Table::CheckTileSecondWithSecondFree(CheckTileData checkTileData) const
{
    if(
        (checkTileData.firstBox.GetValue()  == checkTileData.playerTile.GetSecond() && checkTileData.firstBoxPos == m_secondFreePos)  ||
        (checkTileData.secondBox.GetValue() == checkTileData.playerTile.GetSecond() && checkTileData.secondBoxPos == m_secondFreePos) ||
        (checkTileData.thirdBox.GetValue()  == checkTileData.playerTile.GetSecond() && checkTileData.thirdBoxPos == m_secondFreePos)
        )
    {
        return true;
    }

    return false;
}

void Table::SecondTileMatchWithFirstFree(Tile playerTile, int xPress, int yPress)
{
    std::cout << "Add tile. Second tile box = First free." << std::endl;

    m_firstFreeValue = playerTile.GetFirst();
    m_firstFreePos.x = xPress;
    m_firstFreePos.y = yPress;

    Vector2D tilePos { xPress, yPress };
    AddTile(playerTile, tilePos);
}

void Table::SecondTileMatchWithSecondFree(Tile playerTile, int xPress, int yPress)
{
    std::cout << "Add tile. Second tile box = Second free." << std::endl;

    m_secondFreeValue = playerTile.GetFirst();
    m_secondFreePos.x = xPress;
    m_secondFreePos.y = yPress;

    Vector2D tilePos { xPress, yPress };
    AddTile(playerTile, tilePos);
}

void Table::CreateMap()
{
    for(int row = 0; row < GetMatrixPiecesInRow(); ++row)
    {
        for(int col = 0; col < GetMatrixPiecesInRow(); ++col)
        {
            m_tableBox[row][col].SetPosition(GetMatrixX() + col * GetMatrixPieceSize(), GetMatrixY() + row * GetMatrixPieceSize());
		}
	}

	std::cout << "Map is created!" << std::endl;
}

void Table::Render() const
{
    for(int row = 0; row < GetMatrixPiecesInRow(); ++row)
    {
        for(int col = 0; col < GetMatrixPiecesInRow(); ++col)
        {
            m_tableBox[row][col].Render();  
		}
	}
}

void Table::SetRenderer(SDL_Renderer* renderer)
{
    m_renderer = renderer;

    for(int row = 0; row < GetMatrixPiecesInRow(); ++row)
    {
        for(int col = 0; col < GetMatrixPiecesInRow(); ++col)
        {
            m_tableBox[row][col].SetRenderer(m_renderer);
		}
	}
}

void Table::Clear()
{
    for(int row = 0; row < GetMatrixPiecesInRow(); ++row)
    {
        for(int col = 0; col < GetMatrixPiecesInRow(); ++col)
        {
            m_tableBox[row][col].SetValue("*");
		}
    }
}

std::string Table::WriteTableData() const
{
    std::string data = m_firstFreeValue + " "
                       + m_secondFreeValue + " "
                       + std::to_string(m_firstFreePos.x) + " " + std::to_string(m_firstFreePos.y) + " "
                       + std::to_string(m_secondFreePos.x) + " " + std::to_string(m_secondFreePos.y) + " ";

    for(int row = 0; row < TABLE_SIZE; ++row)
    {
        for(int col =0; col < TABLE_SIZE; ++col)
        {
            data += m_tableBox[row][col].GetValue() + " ";
        }
    }

    data += "\n";

    return data;
}

void Table::SetTableData(std::vector<std::string> tableData)
{
    m_firstFreeValue  = tableData[0];
    m_secondFreeValue = tableData[1];
    m_firstFreePos.x  = std::stoi(tableData[2]);
    m_firstFreePos.y  = std::stoi(tableData[3]);
    m_secondFreePos.x = std::stoi(tableData[4]);
    m_secondFreePos.y = std::stoi(tableData[5]);

    int count = 5;
    std::string token;
    for(int row = 0; row < TABLE_SIZE; row++)
    {
        for(int col = 0; col < TABLE_SIZE; col++)
        {
            // int row = GetMatrixX() + i * GetMatrixPieceSize();
            // int col = GetMatrixY() + y * GetMatrixPieceSize();
            count++;
            m_tableBox[row][col].SetValue(tableData[count]);
        }
    }
}
