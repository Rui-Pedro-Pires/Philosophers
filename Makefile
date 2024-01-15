all:
	@make -C ./philo 

bonus:
	@make -C ./philo_bonus 

clean:
	@make clean -C ./philo -s

fclean:
	@make fclean -C ./philo -s

clean_bonus:
	@make clean -C ./philo_bonus -s

fclean_bonus:
	@make fclean -C ./philo_bonus -s

re: fclean all

re_bonus: fclean_bonus bonus 