#include "FortranTokenLexer.h"
#include "FortranTokenParser.h"

/* globals used by the token parser
 */
pANTLR3_VECTOR         tlist;
pANTLR3_TOKEN_FACTORY  tfactory;
pANTLR3_STRING_FACTORY sfactory;

pANTLR3_VECTOR get_tokens(const char * token_file)
{
   int i;

   pANTLR3_INPUT_STREAM           tinput;
   pFortranTokenLexer             tlexer;
   pANTLR3_COMMON_TOKEN_STREAM    tstream;
   pFortranTokenParser            tparser;

   /* initialize
    */
   tlist     = antlr3VectorNew                   ( 0 );
   tinput    = antlr3FileStreamNew               ( (pANTLR3_UINT8) token_file, ANTLR3_ENC_8BIT );
   tfactory  = antlr3TokenFactoryNew             ( tinput );
   sfactory  = antlr3StringFactoryNew            ( ANTLR3_ENC_8BIT );
   tlexer    = FortranTokenLexerNew              ( tinput );
   tstream   = antlr3CommonTokenStreamSourceNew  ( ANTLR3_SIZE_HINT, TOKENSOURCE(tlexer) );
   tparser   = FortranTokenParserNew             ( tstream );

   tparser->ftokens(tparser);

   /* must manually clean up
    */
   tparser  ->free(tparser);
   tstream  ->free(tstream);
   tlexer   ->free(tlexer);
   tinput   ->close(tinput);

   return tlist;
}
