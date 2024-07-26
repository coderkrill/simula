#pragma once

#include <iostream>
#include <vector>
#include <cassert>

#include "SFML/Graphics.hpp"

class Quad{
    private:
        std::array<sf::Vertex, 4> m_quad;
    public:
        Quad();
        void set_tex_size(const sf::Vector2f& size);
        void set_tex_pos(const sf::Vector2f& pos);
        void set_quad_size(const sf::Vector2f& size); 
        void set_quad_pos(const sf::Vector2f& pos);
        void set_color(const sf::Color& color);
        void print();
        sf::Vertex& operator[] (const size_t& index);
};

Quad :: Quad(){}

void Quad :: set_tex_size(const sf::Vector2f& size){
    const sf::Vector2f pos = m_quad[0].texCoords;
    m_quad[1].texCoords = sf::Vector2f(pos.x + size.x, pos.y         );
    m_quad[2].texCoords = sf::Vector2f(pos.x + size.x, pos.y + size.y);
    m_quad[3].texCoords = sf::Vector2f(pos.x         , pos.y + size.y);
}

void Quad :: set_tex_pos(const sf::Vector2f& pos){
    const sf::Vector2f dif = pos - m_quad[0].texCoords;
    m_quad[0].texCoords += dif;
    m_quad[1].texCoords += dif;
    m_quad[2].texCoords += dif;
    m_quad[3].texCoords += dif;
}

void Quad :: set_quad_size(const sf::Vector2f& size){
    const sf::Vector2f pos = m_quad[0].position;
    m_quad[1].position = sf::Vector2f(pos.x + size.x, pos.y         );
    m_quad[2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
    m_quad[3].position = sf::Vector2f(pos.x         , pos.y + size.y);
}

void Quad :: set_quad_pos(const sf::Vector2f& pos){
    const sf::Vector2f dif = pos - m_quad[0].position;
    m_quad[0].position += dif;
    m_quad[1].position += dif;
    m_quad[2].position += dif;
    m_quad[3].position += dif;
}

void Quad :: set_color(const sf::Color& color){
    m_quad[0].color = color;
    m_quad[1].color = color;
    m_quad[2].color = color;
    m_quad[3].color = color;
}

void Quad :: print(){
    std::cout << "pos.x\tpos.y\ttex.x\ttex.y\tcolor\n";
    for(int i = 0; i<4; i++){
        std::cout << m_quad[i].position.x << "\t" << m_quad[i].position.y << "\t";
        std::cout << m_quad[i].texCoords.x << "\t" << m_quad[i].texCoords.y << "\t";
        std::cout << m_quad[i].color.toInteger() << "\n";
    }
}

sf::Vertex& Quad :: operator[] (const size_t& index){
    return m_quad[index];
}






class QuadVector : public sf::Drawable{
    private:
        std::vector<Quad> m_quads;
        sf::Texture* m_texture;
    public:
        QuadVector();
        QuadVector(const size_t& size);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void set_texture(sf::Texture* texture);
        void resize(const size_t& size);
        void reserve(const size_t& size);
        Quad& operator [] (const size_t& index);
        Quad& at(const size_t& index);
        size_t size() const;
        size_t capacity() const;
        void push(const Quad& quad);
        void pop();
};

QuadVector :: QuadVector()
{

}

QuadVector :: QuadVector(const size_t& size)
{
    m_quads.resize(size);
}

void QuadVector :: draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.texture = m_texture;
    target.draw((sf::Vertex*)&m_quads[0], m_quads.size()*4, sf::Quads, states);
}

void QuadVector :: set_texture(sf::Texture* texture){
    m_texture = texture;
}

void QuadVector :: resize(const size_t& size){
    m_quads.resize(size);
}

void QuadVector :: reserve(const size_t& size){
    m_quads.reserve(size);
}

Quad& QuadVector :: operator [] (const size_t& index){
    return m_quads[index];
}

Quad& QuadVector :: at(const size_t& index){
    return m_quads.at(index);
}

size_t QuadVector :: size() const{
    return m_quads.size();
}

size_t QuadVector :: capacity() const{
    return m_quads.capacity();
}

void QuadVector :: push(const Quad& quad){
    m_quads.push_back(quad);
}

void QuadVector :: pop(){
    m_quads.pop_back();
}