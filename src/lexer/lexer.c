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

// !!!hiç birşey yapılmayacak;
//$ls
// bash-3.2$ >ls
// bash-3.2$ <ls


static void	count_token(t_lexer *t_lex)
{
	while (t_lex->input[t_lex->i])
	{
		if (t_lex->ERRFLAG)
			break;
		else if (t_lex->input[t_lex->i] == '\'' || t_lex->input[t_lex->i] == '"')
			skip_quot(t_lex, t_lex->input[t_lex->i]);
		else if (!ft_strchr("<>| ", t_lex->input[t_lex->i]))
			skip_cmnd_arg(t_lex);
		else if (ft_strchr("<>|", t_lex->input[t_lex->i]))
			skip_operator(t_lex);
		else
			t_lex->i++;
	}
	printf("count token:	%d\n", t_lex->count_token);
}

char	*ft_str_cat(char *dest, char src)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!dest)
	{
		printf("dest:\n");
		tmp = malloc(sizeof(char) * 2);
		tmp[0] = src;
		tmp[1] = '\0';
	}
	else
	{
		while (dest[i])
			i++;
		tmp = malloc(sizeof(char) * i + 2);
		i = 0;
		while (dest[i])
		{
			tmp[i] = dest[i];
			i++;
		}
		tmp[i++] = src;
		tmp[i] = '\0';
		free(dest);
	}
	return (tmp);
}

void	quot_add(t_lexer *t_lex)
{
	t_lex->tmp = t_lex->input[t_lex->i];
	while (t_lex->input[t_lex->i])
	{
		t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		if (t_lex->input[t_lex->i] == t_lex->tmp)
		{
			t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
			break;
		}
	}
	if (ft_strchr("< >|", t_lex->input[t_lex->i]) && !t_lex->input[t_lex->i])
	{
		t_lex->k++;
		return ;
	}
	else
	{
		while (t_lex->input[t_lex->i] && !ft_strchr("< >|", t_lex->input[t_lex->i]))
			t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		t_lex->k++;
	}
}

void	operator_add(t_lexer *t_lex)
{
	if (t_lex->input[t_lex->i] == '|')
	{
		t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		t_lex->k++;
	}
	else if (is_great(t_lex) || !is_great(t_lex))
	{
		if (t_lex->input[t_lex->i + 1] == t_lex->input[t_lex->i])
			t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
		t_lex->k++;
	}
}

void	lex_sep(t_lexer *t_lex)
{
    while(t_lex->input[t_lex->i])
    {
		while (t_lex->input[t_lex->i] && t_lex->input[t_lex->i] == ' ')
			t_lex->i++;
		if (t_lex->input[t_lex->i] == '\'' || t_lex->input[t_lex->i] == '"')
			quot_add(t_lex);
		if (t_lex->input[t_lex->i] && ft_strchr("<>|", t_lex->input[t_lex->i]))
			operator_add(t_lex);
		if (t_lex->input[t_lex->i] && !ft_strchr("<>|\"'", t_lex->input[t_lex->i]))
		{
			while (t_lex->input[t_lex->i] && t_lex->input[t_lex->i] != ' ' &&
				!ft_strchr("<>|\"'", t_lex->input[t_lex->i]))
				t_lex->token[t_lex->k] = ft_str_cat(t_lex->token[t_lex->k], t_lex->input[t_lex->i++]);
			t_lex->k++;
		}
    }
    t_lex->token[t_lex->k] = NULL;
    return ;
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
	if (t_lex.ERRFLAG || !t_lex.count_token)
		return (NULL);
	t_lex.token = ft_calloc(sizeof(char *), t_lex.count_token + 1);
	reset_ver(&t_lex);
	// printf("reset\n");
	lex_sep(&t_lex);
	t_lex.tmp = 0;
	while (t_lex.token[t_lex.tmp])
		printf("func:	%s\n", t_lex.token[t_lex.tmp++]);
	return (t_lex.token);
}

