#include "Design_mode.h"

void Design_mode::draw_dm(std::vector<std::vector<int>>field)
{
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "", sf::Style::Titlebar | sf::Style::Close);

    sf::View view = window.getDefaultView();
    view.zoom(0.33f);
    window.setView(view);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        
        sf::Texture texture_blocks;
	    texture_blocks.loadFromFile("sprites.png");
	    sf::Sprite s_blocks(texture_blocks);

        s_blocks.setTextureRect(sf::IntRect(0, 0, constants::BLOCK_LENGHT * constants::NUMBER_TYPE_OF_BLOCKS, constants::BLOCK_LENGHT));
        s_blocks.setPosition(0, 0);   
        s_blocks.move(constants::WINDOW_OFFSET * 4 / 3, constants::WINDOW_OFFSET * 4 / 3);
        window.draw(s_blocks);

        sf::Texture texture_tiles;
        texture_tiles.loadFromFile("tiles.png");
        sf::Sprite s_tiles(texture_tiles);

        s_tiles.setTextureRect(sf::IntRect(0, 0, constants::TILES_LENGHT * constants::NUMBER_TYPE_OF_TILES, constants::TILES_LENGHT));
        s_tiles.setPosition(0, 0);
        s_tiles.move(constants::WINDOW_OFFSET * 4 / 3, constants::WINDOW_OFFSET * 4 / 3 + 16);
        window.draw(s_tiles);
        
        /*s_blocks.setTextureRect(sf::IntRect((int)constants::Blocks::GRAY * constants::BLOCK_LENGHT, 0, constants::BLOCK_LENGHT, constants::BLOCK_LENGHT));
        for (int i = 0; i < constants::FIELD_HEIGHT; ++i)
            for (int j = 0; j < constants::FIELD_WIDTH; ++j)
            {
                if (field[i][j] == constants::Tiles::GRAY)
                {
                    s_blocks.setPosition(i * constants::BLOCK_LENGHT, j * constants::BLOCK_LENGHT);
                    j += 2;
                }
                s_blocks.move(constants::WINDOW_OFFSET * 4 / 3, constants::WINDOW_OFFSET * 4 / 3 + 32);
                window.draw(s_blocks);
            }*/

        window.display();
    }
	
}