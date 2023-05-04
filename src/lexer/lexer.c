#include "lexer.h"

// pipe qutoe "$"->çalışır '$'->dolar işaretini yazdırır
// shell simple comands ve compound(bileşik) commands olarak ayırır

// 2.2 quoting
//	Alıntı, belirli karakterlerin veya kelimelerin özel anlamlarını kabuğa kaldırmak için kullanılır
//	Karakterleri tek tırnak ( '' ) içine almak, tek tırnak içindeki her karakterin değişmez değerini koruyacaktır. 
// 	!!!!!Tek tırnak içinde tek tırnak olamaz.!!!!!
//	Karakterleri çift tırnak ( "" ) içine almak, aşağıdaki gibi dolar işareti, ters tırnak ve ters eğik çizgi karakterleri dışında, 
// 	çift tırnak içindeki tüm karakterlerin değişmez değerini koruyacaktır: 
//  !!!!echo "'$PATH'" önemli!!!!!
// 	tırnaktan tırnağa alıntılama yapılır.

// 2.3 Token Recognition(belirteç tanıma)
//	ls -l home bunu tokenlarına ayırdığımız zaman
// 		.ls .-l .home şeklinde ayrılıyor
//	echo "Hello" > output.txt #operator
// 	.echo ."Hello" #> .output.txt
// 	tırnak içinde değilse önceki karakter boşluk olur diğer türlü sayılmaz
// 	lexxer tokenlarına göre bölme işlemi yapacak
//	parser ise operatörlere göre bir tablo oluşturacak
// 	operator => << >> < > |
// 	special parametres $ ?

// tokenlara böl
// 		tırnak durumlarını değerlendir 
// 		operatörlere göre böl
// 		boşluk tırnak içindeyken geçerli
// 		ls|grep d => çalışır.
// 		boşluklardan sonra komut başlar

int	quo_count(int quo, char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == quo)
			count++;
		i++;
	}
	return (count);
}

void	reset_ver(t_lexer *t_lex)
{
	t_lex->i = 0;
	t_lex->tmp = 0;
	t_lex->count_token = 0;
	t_lex->is = 0;
	t_lex->ERRFLAG = 0;
}

int	is_valid_quot(t_lexer *t_lex, char quot)
{
	if (t_lex->input[t_lex->i + 1] == quot && t_lex->input[t_lex->i + 2]
		&& !ft_strchr(" <>|", t_lex->input[t_lex->i + 2]))
	{
		t_lex->i += 2;
		return (0);	
	}
	if (t_lex->i > 0 && !ft_strchr(" <>|", t_lex->input[t_lex->i - 1]))
	{
		t_lex->i += 2;
		return (0);
	}
	return (1);
}

void	skip_quot(t_lexer *t_lex, char quot)
{
	t_lex->is = 1;
	if (!is_valid_quot(t_lex, t_lex->input[t_lex->i]))
		return ;
	t_lex->tmp = 1;
	while (t_lex->input[t_lex->i])
	{
		t_lex->i++;
		if (t_lex->input[t_lex->i] == quot)
			t_lex->tmp++;
		if (t_lex->input[t_lex->i] && t_lex->input[t_lex->i] == quot
			&& t_lex->input[t_lex->i + 1] && t_lex->input[t_lex->i + 1] == quot)
			continue;
		else if (t_lex->input[t_lex->i] && t_lex->input[t_lex->i] == quot
			&& t_lex->tmp % 2 == 0)
		{
			t_lex->i++;
			break;
		}
	}
	t_lex->count_token++;
}

void	skip_cmnd_arg(t_lexer *t_lex)
{
	while (t_lex->input[t_lex->i])
	{
		if (ft_strchr(" <>|", t_lex->input[t_lex->i]))
			break ;
		t_lex->i++;
	}
	t_lex->count_token++;
}

int	is_great(int i)
{
	if (i == '>')
		return (1);
	return (0);
}

void	red_cntrl(t_lexer *t_lex)
{
	if (t_lex->input[t_lex->i + 1] && t_lex->input[t_lex->i] == t_lex->input[t_lex->i + 1])
		t_lex->i++;
	if (!t_lex->input[t_lex->i + 1])
	{
		printf("bash: syntax error near unexpected token 'newline'");
		t_lex->ERRFLAG = 1;
	}
	else if (is_great(t_lex->input[t_lex->i]) && t_lex->input[t_lex->i] == '<')
	{
		printf("bash: syntax error near unexpected token '<'");
		t_lex->ERRFLAG = 1;
	}
	else if (!is_great(t_lex->input[t_lex->i]) && t_lex->input[t_lex->i] == '>')
	{
		printf("bash: syntax error near unexpected token 'newline'");
		t_lex->ERRFLAG = 1;
	}
	else if (t_lex->input[t_lex->i + 1] && t_lex->input[t_lex->i + 1] == t_lex->input[t_lex->i])
	{
		t_lex->i += 2;
		t_lex->count_token++;
	}
	else
	{
		t_lex->i++;
		t_lex->count_token++;
	}
}

void	skip_operator(t_lexer *t_lex)
{
	if (t_lex->input[t_lex->i] == '<' || t_lex->input[t_lex->i] == '>')
		red_cntrl(t_lex);
}

void	count_token(t_lexer *t_lex)
{
	while (t_lex->input[t_lex->i])
	{
		if (t_lex->ERRFLAG)
			break;
		if (t_lex->input[t_lex->i] == '\'' || t_lex->input[t_lex->i] == '"')
			skip_quot(t_lex, t_lex->input[t_lex->i]);
		if (ft_isalpha(t_lex->input[t_lex->i]))
			skip_cmnd_arg(t_lex);
		if (ft_strchr("<>|", t_lex->input[t_lex->i]))
			skip_operator(t_lex);
		if (!t_lex->is)
			t_lex->i++;
		t_lex->is = 0;
	}
}

char	**lexer()
{
	t_lexer	t_lex;

	t_lex.s_quo = quo_count('\'', g_data.input);
	t_lex.d_quo = quo_count('"', g_data.input);
	if (t_lex.s_quo % 2 != 0 || t_lex.d_quo % 2 != 0)
	{
		printf("missing quote\n");
		return (NULL);
	}
	t_lex.input = ft_strdup(g_data.input);
	reset_ver(&t_lex);
	count_token(&t_lex);
	if (t_lex.ERRFLAG)
		return (NULL);
	printf("count token:	%d\n", t_lex.count_token);
	return (t_lex.token);
}

