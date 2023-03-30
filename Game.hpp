/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles <rteles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:00:29 by rteles            #+#    #+#             */
/*   Updated: 2023/03/30 11:58:35 by rteles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <ctime>

class Game
{
    private:
        std::string                 _room;
        int                         _game;
        clock_t                     _start;
        int                         _time;
        std::vector<std::string>    _winners;
        std::vector<std::string>    _draws;
        std::vector<std::string>    _losers;
        std::string                 _vitory;
        int                         _result;
        int                         _reward;
        Game();

    public:
        Game(std::string room, int game, int time, int reward);
        ~Game();

        int                         getGame(void) const{ return _game; }
        std::string                 getRoom(void) const{ return _room; }
        int                         getResult(void) const{ return _result; }
        int                         getReward(void) const{ return _reward; }
        clock_t                     getStartTime(void) const{ return _start; }
        int                         getTimeLimit(void) const{ return _time; }
        std::vector<std::string>    getWinners(void) const{ return _winners; }
        std::vector<std::string>    getDraws(void) const{ return _draws; }
        std::vector<std::string>    getLosers(void) const{ return _losers; }
        std::string                 getVictory(void) const{ return _vitory; }
        void                        setResult(int result) { _result = result; }
        void                        setVitory(std::string vitory) { _vitory = vitory; }
        void                        setWinnerOrLosser(std::string player, int win)
        {     
            std::vector<std::string>::iterator vector_it;
            
            for (vector_it = _losers.begin(); vector_it != _losers.end(); ++vector_it)
                if (*vector_it == player)
                    return ;
            
            for (vector_it = _draws.begin(); vector_it != _draws.end(); ++vector_it)
                if (*vector_it == player)
                    return ;
            
            for (vector_it = _winners.begin(); vector_it != _winners.end(); ++vector_it)
                if (*vector_it == player)
                    return ;
            
            if (win == 2)
                _winners.push_back(player);
            else if (win == 1)
                _draws.push_back(player);
            else
                _losers.push_back(player);
        }
        
};
