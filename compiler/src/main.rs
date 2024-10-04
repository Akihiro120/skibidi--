use logos::Logos;

#[derive(Logos, Debug)]
enum Token {
    // keywords
    #[token("skibidi")]
    Let,

    // operators
    #[token("fr")]
    Equals,
    #[token("+")]
    Plus,

    // constant
    #[token("on god")]
    Constant,

    // identifiers
    #[regex("[a-zA-Z][a-zA-Z0-9]*")]
    Identifier,

    // numbers
    #[regex("[0-9]+")]
    Number,

    // conparison
    #[token("smol pp")]
    LessThan,
    #[token("big pp")]
    GreaterThan,
    #[token("frfr")]
    Equality,

    #[token("goon to")]
    ForLoop,

    // syntax
    #[token(";")]
    Semicolon,
    #[token("{")]
    LeftBrace,
    #[token("}")]
    RightBrace,

    // functions
    #[token("in ohio")]
    Main,
    #[token("backrooms")]
    Function,
    #[token("with")]
    Parameters,
    #[token("glaze")]
    Return,

    // flow control
    #[token("sus")]
    If,
    #[token("imposter")]
    Else,
    #[token("imposter sus")]
    ElseIf,

    // whitespace
    #[regex(r"[ \t\n\f]+", logos::skip)]
    Whitespace,
}

fn main() {
    // get the main file
    let main_file = std::fs::read_to_string("ohio.skb"); 
    match main_file {
        Err(..) => {
            println!("cant find ohio???");
        }
        Ok(file) => { 
            println!("we in the backrooms");
            lexer_stage(file);
        }
    }
}

fn lexer_stage(content: String) {
    let tokens: Vec<_> = Token::lexer(&content).collect();

}
