/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:00:29 by rteles            #+#    #+#             */
/*   Updated: 2023/03/30 11:57:56 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game(void) {}

Game::Game(std::string room, int game, int time, int reward): _room(room),  _game(game),  _time(time), _reward(reward)
{
    _result = 0;
    _start = clock();
    _vitory = "";
}

Game::~Game() {
    
}
