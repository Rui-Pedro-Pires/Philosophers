all:
	@make -C ./philo 

bonus:
	@make -C ./philo_bonus 

clean:
	@make clean -C ./philo -s
	@make clean -C ./philo_bonus -s

fclean: clean
	@make fclean -C ./philo -s
	@make fclean -C ./philo_bonus -s

re: fclean all

re_bonus: fclean_bonus bonus 