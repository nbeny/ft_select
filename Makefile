# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeny <nbeny@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/12 01:47:28 by nbeny             #+#    #+#              #
#    Updated: 2017/04/12 01:47:32 by nbeny            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_select

N_INC	=	ft_select.h
N_SRC	=	test5.c

CC	=	gcc
CC_FLAG	=	-g -Wextra -lncurses

T_SRC	=	./src/
T_INC	=	./include/
T_OBJ	=	./obj/
T_PTF	=	./ft_printf/

I_INC	=	./include/
I_LFT	=	./libft/include/
I_PTF	=	./ft_printf/include/
L_LFT	=	-L ./ft_printf/libft/ -lft
L_PTF	=	-L ./ft_printf/ -lftprintf

CL_N	=	\033[0m
CL_R	=	\033[31m
CL_V	=	\033[32m
CL_J	=	\033[33m
CL_B	=	\033[34m
CL_C	=	\033[36m

CL_NS	=	\033[0;4m
CL_RS	=	\033[31;4m
CL_VS	=	\033[32;4m
CL_JS	=	\033[33;4m
CL_BS	=	\033[34;4m
CL_CS	=	\033[36;4m

CL_NG	=	\033[0;1m
CL_RG	=	\033[31;1m
CL_VG	=	\033[32;1m
CL_JG	=	\033[33;1m
CL_BG	=	\033[34;1m
CL_CG	=	\033[36;1m

SRC	=	$(addprefix $(T_SRC), $(N_SRC))
OBJ	=	$(addprefix $(T_OBJ), $(N_OBJ))
INC	=	$(addprefix -I, $(I_INC) $(I_LFT) $(I_PTF))

N_OBJ	=	$(N_SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo ">$(CL_V)Build: $(CL_VG)ft_printf$(CL_N)"
	@make -C $(T_PTF)
	@echo ">$(CL_V)Build: $(CL_VG)$(NAME)$(CL_N)"
	@$(CC) $(CC_FLAG) -o $(NAME) $(OBJ) $(L_LFT) $(L_PTF)

$(T_OBJ)%.o: $(T_SRC)%.c
	@echo ">$(CL_V)Creat: Objects files..$(CL_N)"
	@mkdir -p $(T_OBJ)
	@$(CC) $(CC_FLAG) -o $@ -c $^ $(INC)

clean:
	@echo ">$(CL_R)clean: $(CL_B)$(NAME) objects$(CL_N)"
	@rm -Rf $(T_OBJ)
	@make -C $(T_PTF) clean

fclean: clean
	@make -C $(T_PTF) fclean
	@echo ">$(CL_R)Delete: $(CL_B)$(NAME)$(CL_N)"
	@rm -f $(NAME)

re: fclean all
