#pragma once

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

#include "quad.hpp"
#include "colors.hpp"
#include "random/random.hpp"
#include "random/perlin.hpp"

using Realm = int;

class World : public sf::Drawable{
    private:
        sf::Vector2u m_world_size;
        std::vector<Realm> m_realms;
        QuadVector m_realm_quads;
        sf::Texture m_realm_textures;

        void update_quad_position();
        void update_quad_texture();
        
    public:
        World(sf::Vector2u size);
        
        void generate();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void load_texture(std::string filename);
        void update();
};

void World :: update_quad_position(){
    const float TILE_SIZE = 4.0f;
    for(size_t y = 0; y<m_world_size.y; y++){
        for(size_t x = 0; x<m_world_size.x; x++){
            size_t index = x + y * m_world_size.x;
            m_realm_quads.at(index).set_quad_pos({TILE_SIZE * x, TILE_SIZE*y});
            m_realm_quads.at(index).set_quad_size({TILE_SIZE, TILE_SIZE}); 
        }   
    }
}
void World :: update_quad_texture(){
    for(int i = 0; i<m_realm_quads.size(); i++){
        uint8_t color = m_realms.at(i);
             if(color < 64 ) m_realm_quads.at(i).set_color(ocean1);
        else if(color < 96 ) m_realm_quads.at(i).set_color(ocean2);
        else if(color < 128) m_realm_quads.at(i).set_color(ocean3);
        //else if(color < 128) m_realm_quads.at(i).set_color(land1);
        else if(color < 160) m_realm_quads.at(i).set_color(land2);
        else if(color < 192) m_realm_quads.at(i).set_color(land3);
        else if(color < 224) m_realm_quads.at(i).set_color(rock1);
        else                 m_realm_quads.at(i).set_color(rock2);
    }
}

World :: World(sf::Vector2u size){
    m_world_size = size;
    m_realm_quads.resize(size.x * size.y);
    m_realm_quads.set_texture(&m_realm_textures);
    m_realms.resize(size.x * size.y);
    generate();
    update_quad_position();
    update_quad_texture();
}

void World :: generate(){
    Xor128 rng;
    PerlinNoise noise(rng());

    const sf::Vector2u size = m_world_size;
    sf::Vector2u low_size = {100,100};
    sf::Vector2u med_size = {50,50};
    sf::Vector2u hig_size = {20,20};
    for(int y = 0; y<size.y; y++){
        for(int x = 0; x<size.x; x++){
            float f0 = noise.sample(sf::Vector2f(x,y), low_size);
            float f1 = noise.sample(sf::Vector2f(x,y), med_size);
            float f2 = noise.sample(sf::Vector2f(x,y), hig_size);

            float f = 1.5 * (f0 + f1/2 + f2/2);
            if(f >  1.0) f =  1.0;
            if(f < -1.0) f = -1.0;
            m_realms.at(x + y * m_world_size.x) = 255 * ((f/2) + 0.5);
        }
    }

    for(int y = 0; y<size.y; y++){
        for(int x = 0; x<size.x; x++){
            float dfx = (x==0 || x==size.x-1) ? 0 : (m_realms.at((x+1) + (y+0)*size.x)-m_realms.at((x-1) + (y+0)*size.x))/2;
            float dfy = (y==0 || y==size.y-1) ? 0 : (m_realms.at((x+0) + (y+1)*size.x)-m_realms.at((x+0) + (y-1)*size.x))/2;
        }
    }
}

void World :: draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_realm_quads);
}

void World :: load_texture(std::string filename){
    m_realm_textures.loadFromFile(filename);
}

void World :: update(){
    
}

