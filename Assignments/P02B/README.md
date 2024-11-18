- Class Dice
    - Attributes
        - Sides
        - Current_value
    - Action Methods 
        - Roll() 
        - Get_value() 
    - Relationships
        - Interacts with Player class
            
- Class PLayer
    - Attributes
        - Name
        - Team
        - Score
        - Grid
        - Dice_set
        - Player_stats
    - Action Methods
        - Roll_Dice()
        - Place_dice()
        - Remove_opponent_dice()
        - Set_team()
        - Get_score()
        - Update_score()
    - Relationships
        - Player HAS-A Dice
        - Player IS-A participant
        - Interacts with Game class

- Class Game
    - Attributes
        - Current_round
        - Rules
        - Players
        - Teams
    - Methods
        - Start_game()
        - End_game()
        - Set_teams()
        - Get_winner()
        - Turn()
        - Next_turn()
    - Relationships
        - Game HAS-A Player
        - Interacts with Knucklebones class


- Class Knucklebones
    - Attributes
        - Board
        - Knucklebones_specific_rules
        - Leaderboard
        - Game_score
        - Teams
        - Game_bracket
        - Winner
        - Streak
    - Methods
        - Start_round()
        - End_round()
        - Update_leaderboard()
        - Calculate_score()
        - Update_streak()
    - Relationships
        - Interacts with Game class
        - Interacts with player class
        

        

