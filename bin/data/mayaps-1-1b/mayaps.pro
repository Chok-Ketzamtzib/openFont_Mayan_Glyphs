%
%  mayaps.pro  ps prolog for mayaps v 1.1b  March 2, 2017
%              can be used together with  mayaps.tex v 1.1b
%
%    author:   Stepan Orevkov
%

userdict begin TeXDict begin/m@Ya{div currentpoint 3 2 roll currentpoint
   gsave translate 1 scale neg exch neg exch translate}bind def end

/MayaDict 44 dict def MayaDict begin

% gi,pd,ie,bd,Udf,mdf0,parse,CorDep,PaS1,PaS2,PaS3,PreParse,Di,DT,PM-ac,PM,
% ApplyTr,Tr,cvpt,E,ng,GIni,GEnd,GDict,GGDict, GDicts,GGDicts, ExtArr,
% NFonts, NewFont, NewF, NewFt, NF1, NF2, SkipFont, SkF, Si, AddGlyphs, AG,
% ColorDict, RGB, showpage, imp,imp1

/gi{getinterval}def/pd{putinterval dup}def
/ie{ifelse}def/bd{bind def}def/showpage{}def
/ColorDict 100 dict def/RGB{true}def

         % Draw a framed gray rectangle with the glyph name (if undefined)
/Udf{
  gsave newpath .01 dup moveto .99 .01 lineto .99 dup lineto .01 .99 lineto
  closepath gsave .9 setgray fill grestore gsave .02 setlinewidth stroke
  grestore clip dup length 3 le{0.45}{0.38}ie /Helvetica findfont exch
  scalefont setfont dup length 4 le{0.1 0.35}{0.1 0.58 moveto dup 0 4 gi
  show 4 1 index length 4 sub gi 0.1 0.2}ie moveto show grestore
}bd

                            % Default LURDS-array
/mdf0[()(|r)(|)(R)()]def

%===========================================================================
%
%  the recursive procedure
%  usage:   s -> parse -> proc w h tr [LURDS] is_aff
%  where:   s      : code of a (composed) maya glyph, e.g. ((123.234):345)
%           proc   : procedure to draw the glyph
%           w h    : width and height of the glyph
%           tr     : element of dihedral group (number in [0..7])
%                    this is the modification from the calling sequence
%           [LURDS]: (only if is_aff is true) array of strings of modifiers 
%                    (some of -,+,|,R,r,?,*)
%           is_aff : (bool) is true if the glyph is an affix
%
%  When  parse  is called, we suppose that  GDict  is defined as the 
%  glyph dictionary of the current font, i.e. the f-th element of the
%  array GDicts. This definition is performed in E. More details about
%  GDict  see in the section "Multifont Support" below
%
/parse{
  % unnamed (since recursive!) dictionary:
  36 dict begin

  %  s,n,k,k0,subr,inpar,dep,c,horiz,delim,i,i0,na,name       the names used
  %  sb,h,w,x,y,b,sa,C,sC,m,a,ia,ia1,mdf,D,LD,LG,posC         in this dict
  %  ab (added in Oct 2016)

  /s exch def/n s length def/k 0 def/i0 0 def

                % both of ":" and "/" are accepted as a vertical delimiter
  0 1 n 1 sub{dup s exch get 47 eq{s exch 58 put}{pop}ie}for
                           % 47='/'       58=':'

                                   % remove all exterior parentheses (PaS1)
  PaS1

                                   % decide the mode (horiz/vert)
  /dep 0 def/horiz false def
  0 1 n 1 sub{s exch get/c exch def
     dep 0 eq{c 46 eq{/horiz true def exit}if}if CorDep
               %46='.'
  }for
  /delim horiz{46}{58}ie def
           % 46='.' 58=':'

  /dep 0 def/k 1 def /i0 0 def
  0 1 n 1 sub{/i exch def /c s i get def
     dep 0 eq{c delim eq{
         s i0 i i0 sub gi horiz{k 1 roll}if
                         %see remark (**) below
         /i0 i 1 add def/k k 1 add def
     }if}if
     CorDep
  }for
  s i0 n i0 sub gi horiz{k 1 roll}if
                  %see remark (**) below
  
  %   (**)  the order of primitive glyphs is
  %         either up->down (as -y coord) or left->right (as +x coord)
  %         this is why in the horizontal mode we put the glyphs on the
  %         stack in the reverse order in the above loop

                                     %  THE CASE k=1 :
                                     %    EITHER A PRIMITIVE GLYPH
                                     %    OR A GLYPH IN () WITH A MODIFIER
                                     %    (at this stage, XXX<YYY> is
                                     %     considered as primitive)

  k 1 eq{pop /c n 0 gt{s 0 get}{0}ie def

    %   here s contains the glyph name, maybe preceded
    %   by a modificator (arguments) and/or followed by
    %   a color indicator,   n = length(s)

    PaS2

    % now s is the glyph name and  sa  is the string of modifiers without []
    % color indicator -> b

                                      %  THE SUBCASE OF A PRIMITIVE GLYPH

    s length 0 gt{s 0 get}{0}ie 40 ne{MayaDict/ng ng 1 add put
                              % 40 = '('

%===== added in October 2016 (infixation support) ======
                              % extract the part in <...> and put it to ab
      /ab 0 string def
      s length 0 gt{s n 1 sub get 62 eq{
                  % 62 = '>'
          0 1 n 1 sub{/i exch def
              s i get 60 eq{/n n 2 sub i sub def
                    % 60 = '<'
                    /ab s i 1 add n gi def/s s 0 i gi def/n i def exit
              }if
          }for
      }if}if
%=======================================================

      /name n 1 add string def /a{[s/Udf cvx] 1 1 0 false}def
      /subr{name copy pop s name 1 n gi copy pop name}bd
      (m) subr token{
                                      % get token from "(m)|name"
        exch length 0 eq{
                                      % if it is of the full length and
           GDict exch known{
              b length 0 eq{name cvn}{b 6 name cvn cvx put b bind}ie
                                      % if it is known, leave it on the stack
              (w) subr cvx cvn load
              (h) subr cvx cvn load
                                      % and leave w h on the stack also
              /ia
              (a) subr cvx cvn load def
                                      % ia = is_affix ( = true if affix )
              /mdf
              (A) subr cvx cvn dup GDict exch
              known{load}{pop mdf0}ie def

              0 PaS3
                           %
                           % Finally, we leave  w h tr [modif] true
                           %                or  w h tr false
                           % where tr is a number 0..7 representing
                           % an element of the dihedral group
           }{a}ie
        }{pop a}ie
      }{a}ie

%=========== Added in October 2016 (infixation support) ===========
%     Modified Feb 25, 2017: Infix Scale Factors are added
                                      % if affix then we ignore the <...> part
      dup not ab length 0 ne and{/w 4 index def/h 3 index def
        ab parse/ia exch def ia{4 get PM}if ApplyTr
        /y exch def/c h y div ISFy mul def
        /x exch def/a w x div ISFx mul def
        ia{a c lt{/c a}{/a c}ie def}if
        /x w a x mul sub 2 div def
        /y h c y mul sub 2 div def
        [/gsave cvx x y/translate cvx a c/scale cvx 9 8 roll/cvx cvx
        /exec cvx/grestore cvx 17 16 roll/cvx cvx/exec cvx]bind 5 1 roll
      }if
%=================================================================

    }
                                     % THE SUBCASE OF A GLYPH IN () WITH A
                                     % MODIFIER AND/OR A COLOR INDICATOR

    {  s parse /ia exch def/mdf ia{exch}{mdf0}ie def
       4 3 roll[exch/cvx cvx/exec cvx]
       b length 0 gt{10 array dup 0 b 0 6 gi pd 6 4 3 roll pd 9 b 7 get put
       }if bind 4 1 roll PaS3
    }ie
  }
                                     % THE CASE OF A COMPOSED GLYPH (k>1)

  {  /sb 0 def/a 11 k mul 5 add array def/n 0 def/sC 0 def/m 0 def
                         %% change the meaning of n,c

                         % Let's compute posC such that the glyphs
                         % (0,...,posC-1) are in the left (bottom) position
                         % (posC,...,k-1) are in the right (top) position

     k copy/posC horiz{1}{k 1 sub}ie def
     /D false def/C false def/LG()def/LD false def
                  % D = there are two successive Digits;
                  % C = there is a Central element
                  % LG(string) = the name of the previous glyph
                  % LD(bool)   = the previous glyph was a digit
     0  1  k 1 sub{/i exch def
        PreParse
%                ->  name is_digit is_affix
        horiz{not{/posC i def}if pop pop}{
           C{pop pop pop}{{
                 % if affix
                 D{pop pop}{
                    dup{LD{/posC i 1 sub def/D true def}if
                        % if digit
                    }{
                       % if non-digit affix
                       1 index LG eq{/posC i 1 add def}if
                    }ie/LD exch def
                    /LG exch def
                 }ie
              }
              {/posC i def/C true def pop pop}ie
           }ie
        }ie
     }for/C false def
                        %% posC is computed

     0  1  k 1 sub{dup posC eq{/C true def}if/i exch 11 mul def

        parse
                           %%% recursion !!!

        /ia exch def 
        ia{horiz{C{2}{0}ie}{C{1}{3}ie}ie
              get MayaDict begin PM end
        }if
        ApplyTr/h exch def/w exch def
        horiz{/x w h div def/y 0       def/c 1 h div def/b x def}
             {/x 0       def/y h w div def/c 1 w div def/b y def}ie
        /sb sb b add def
        /sa[c c /gsave cvx /scale cvx null /cvx cvx /exec cvx 
                                    /grestore cvx x y /translate cvx]bd
        sa exch 4 exch put sa a i 4 add 11 gi copy pop
        ia not{/n n 1 add def/sC sC b add def b m gt{/m b def}if}if
     }for

     %/c n 1 gt{m sC div}{1}ie def
     /c 1 sb div def
     /sb sb c mul def
     [/gsave cvx horiz{c 1}{1 c}ie /scale cvx] a 0 4 gi copy pop
     a k 11 mul 4 add /grestore cvx put
     a bind
                    % leave proc on the stack
     horiz{sb 1}{1 sb}ie
                    % leave width and height on the stack
     0 false
                    % leave tr=0 is_affix=false on the stack
  }ie
end}bd

%=========================================================================
%
%  Parse Subroutines:   common parts of `parse' and `PreParse'
%
                                 % correct depth used in PaS1 and in parse
/CorDep{c 40 eq c 60 eq or{dep 1 add /dep exch def}
                        {c 41 eq c 62 eq or{dep 1 sub /dep exch def}if}ie
        % 40='('  60='<'   41=')'  62='>'
}bd

/PaS1{
                                    % remove all exterior parentheses
  {  n 0 eq{exit}if /inpar false def
     s 0 get 40 eq{s n 1 sub get 41 eq{/dep 1 def/inpar true def
           % 40='('              41=')'
        1 1 n 2 sub{s exch get/c exch def
          dep 0 eq{/inpar false def exit}if CorDep  
        }for
     }if}if
     inpar{/s s 1 n 2 sub gi def /n s length def}{exit}ie
  }loop}bd

                             %      arguments       -> sa
                             %      color indicator -> b
/PaS2{
     %   here s contains the glyph name, maybe preceded
     %   by a modificator (arguments) and/or followed by
     %   a color indicator,    n = length(s)

     /na 0 def/dep 0 def/sa n string def/i 0 def
     s{ /c exch def c 91 eq{/dep dep 1 add def/i i 1 add def}
                    % 91 = '['
        {  c 93 eq{dep 0 eq{/sa()def/na 0 def exit}if
           % 93 = ']'
              /dep dep 1 sub def/i i 1 add def
           }
           {  c 39 eq    c 43 eq or c 45 eq or c 124 eq or 
              c 42 eq or c 63 eq or c 61 eq or dep 0 gt or{
                                 % i.e. c is one of ' + - | * ? = or dep>0
                 sa na c 61 eq{99}{c}ie put/na na 1 add def/i i 1 add def
                       % `='   `c'
              }
              {  /sa sa 0 na gi def/n n i sub def/s s i n gi def exit}ie
           }ie
        }ie
     }forall /b[]def
     n 0 gt{
       s n 1 sub get 96 eq{/n n 1 sub def/s s 0 n gi def}{
                     %` (96 = left quote)
         1 1 n{1 sub/i exch def/name n i sub 1 add string def(c)name copy pop
           s i n i sub gi name 1 n i sub gi copy pop name
           token{exch
             length 0 eq{ColorDict exch known{/n i def/s s 0 i gi def
               RGB{/b[/gsave cvx/ColorDict cvx/begin cvx name cvx cvn
                           /setrgbcolor cvx/end cvx null/grestore cvx]def
               % {gsave ColorDict begin cxxx setrgbcolor end mzzz grestore}
               }if exit
             }if}{pop}ie
           }if
         }for
       }ie
       % if s starts with 40="(" then remove all after the last 41=")"
       n 0 gt{s 0 get 40 eq s n 1 sub get 41 ne and{
         n -1 1{/n exch def s n 1 sub get 41 eq{/s s 0 n gi def exit}if}for
       }if}if
     }if
}bd

/PaS3{    /ia1
          ia sa{dup 99 eq 1 index 67 eq or{pop pop false}
                   % *=='c' || *=='C'
               {dup 97 eq exch 65 eq or{pop true}if}ie
                   % *=='a' || *=='A'
          }forall def
          ia ia1 not and{mdf 4 get PM}if sa PM ia1{mdf}if ia1
}bd



%=========================================================================
%
%   s -> PreParse -> name is_digit is_affix
%
%   s         (string)  a code of a composed glyph
%   name      (string)  the glyph name
%   is_digit  (boolean) true if s is a single glyph which is a Maya digit
%                       here `digit' means that the name begins with
%                       a character contained in the string NumIC
%   is_affix  (boolean) true iff  s  is an affix
%
/PreParse{20 dict begin
   /s exch def/n s length def PaS1 PaS2

     % now s is the glyph name and  sa  is the string of modifiers without []

     /name n 1 add string def /a{/ia1 false def/id false def}bd
     /subr{name copy pop s name 1 n gi copy pop name}bd
     (m)subr token{
                                      % get token from "(m)|name"
        exch length 0 eq{
                                      % if it's of the full length and
           GDict exch known{
                                      % if it's known, 
              /ia
              (a) subr cvx cvn load def
                                      % ia = is_affix ( = true if affix )

              /ia1
              ia sa{dup 99 eq 1 index 67 eq or{pop pop false}
                      % *=='c' || *=='C'
                    {dup 97 eq exch 65 eq or{pop true}if}ie
                      % *=='a' || *=='A'
              }forall def

              /id false def
              ia1{s 0 get NumIC{1 index eq id or/id exch def}forall pop}if
                                      % id = is_digit ( = true if digit )
           }{a}ie
        }{pop a}ie
     }{a}ie

     s id ia1
end}bd


%    The multiplication table for the dihedral group
%               R|      R = (90 rotate)  r = (270 rotate)  w.r.t.the center
%
%                 0    |   -   +   R   R|   r   R-
%                 |   ||  |-  |+  |R  ||r  |r  ||R
%                 -   -|  --  -+  -R  --R  -r  --r
%                 +   +|  +-  ++  +R  +-R  +r  +|R
%                 R   R|  R-  R+  RR  Rr-  Rr  Rr|
% R| = r- = -R = |r  R|| R|- R|+ |rR -Rr- -Rr -Rr|
%                 r   r|  r-  r+  rR  rR|  rr  rR-
% R- = r| = |R = -r  r|| r|- r|+ -rR -rR| |Rr -rR-
%
%       | - + R   r R-
/Di [[0 1 2 3 4 5 6 7]
     [1 0 3 2 7 6 5 4]
     [2 3 0 1 5 4 7 6]
     [3 2 1 0 6 7 4 5]
     [4 5 7 6 3 2 0 1]
     [5 4 6 7 1 0 2 3]
     [6 7 5 4 0 1 3 2]
     [7 6 4 5 2 3 1 0]]
def

/DT 256 string def 0 1 255{DT exch 0 put}for
DT 124 1 put DT  45 2 put
%   '|'          '-'
DT  43 3 put DT  82 4 put DT 114 6 put
%   '+'         'R'          'r'
DT  42 6 put DT  63 4 put DT  39 1 put
%   '*'         '?'          '''(apostrof)

% tr w -> PM = Parse Modification -> tr
% where: w   is a string of  -,+,|,R,r
%        tr  is an element of the dihedral group
%
/PM{{DT exch get exch Di exch get exch get}forall}bd

% proc w h tr -> ApplyTr -> proc w h

/ApplyTr{
   dup 0 eq{pop}
   {  6 dict begin/tr exch def/h exch def/w exch def/proc exch def
      tr 4 ge{/hh w def/ww h def}{/hh h def/ww w def}ie
      [/gsave cvx ww 2 div hh 2 div/translate cvx Tr tr get/exec cvx
          w neg 2 div h neg 2 div/translate cvx proc/cvx cvx/exec cvx
          /grestore cvx]cvx bind ww hh end
   }ie
}bd

/Tr[{}{-1 1 scale}bind{1 -1 scale}bind{-1 -1 scale}bind{90 rotate}bind
    {1 -1 scale 90 rotate}bind{270 rotate}bind{-1 1 scale 90 rotate}bind
]def

                                         %% convert pt into bp
/cvpt{655.36 div 72.27 div 72 mul}bd

      %%  to be called by  special{"M GlyphCode w h f E} from mayaps.tex
      %%  where M is defined in mayaps.tex as
      %%  /M {userdict begin MayaDict begin gsave} def
      %%  GlyphCode w h  are the arguments of  parse
      %%  f  is the font.
      %%  The procedure  parse  sets  ng (in MayaDict) to be equal to
      %%  the number of primitive glyphs.
/E{
  dup GDicts exch get/GDict exch def GGDicts exch get/GGDict exch def
  GDict begin 11 dict begin MayaDict/ng 0 put
  /h exch cvpt def/w exch cvpt def/ndot true 2 index{46 ne and}forall def
  parse /aff exch def aff{4 get 0 exch PM exch Di exch get exch get}if
  ApplyTr/hh exch def/ww exch def
  /w0 ndot{w h add 2 div}{w}ie def
  /kx w0 ww div def/ky h hh div def
  ng 1 eq{/kx ky kx min def/ky kx def}if
  ndot{w kx ww mul sub 2 div 0 translate}if
  kx ky scale cvx exec grestore end end end end
}bd

%======================================================================
%                           Multifont support
%
%   The dictionary  MayaDict  contains arrays  GDicts  and  GGDicts
%   Initially the formal length of each of them is 32, but only  NFonts
%   elements are actually used. Initially NFonts=0. 
%
%   Each element of GDicts (resp. of GGDicts) is a dictionary
%   (the f-th element corresponds to the f-th font). It is denoted 
%   by GDict (resp. by GGDict) when the command parse is being executed.
%
%   The dictionary GDict=GDicts[f] contains at most 5n+1 key-value pairs
%   where  n  is the number of glyphs in the f-th font. These are:
%
%   NumIC:  a string containing all characters which are used as the
%           initial characters of Maya numerals (digits).
%           The value used in the font `codex' is (89).
%
%   InfixSF: (optional) a number. Infix Scale Factor. Default value 0.75
% 
%    mxxx:  the PS-program of drawing the primitive glyph  xxx;
%    wxxx:  the width of  xxx;
%    hxxx:  the height of  xxx;
%    axxx:  true if  xxx  is an affix, false if not;
%    Axxx:  (optional) the array of modifiers [(L)(U)(R)(D)(S)].
%
%   The dictionary  GGDict=GGDicts[f]  contains definitions which are
%   used in the programs  mxxx
%
%----------------------------------------------------------------------

%----
%   k arr  ->ExtArr->  arr'
%   Increase the length of an array arr by k
%
/ExtArr{dup length 3 2 roll add array dup 3 1 roll copy pop}bd

%----
%   s n  ->NewFt->  -
%
%   s  (string) the value of NumIC
%   n  (integer) the capacity of GGDict
%
%   Increase by 1 the value of NFonts;
%   Create a new dict with only 3 key-value pairs NumIC = s,
%   ISFx = 0.65 ISFy = 0.6 and put it to the end of the array GDicts;
%   Create a new dict of capacity  n+1, put it to the end of GGDicts,
%   and make it current (i.e. put it on the top of the dict stack).
%   Define /iFont = f in this dict, where f is the font descriptor.
%   If the length of GDicts is exceeded, extend it.
%   This program should be called when  MayaDict  is on the top of
%   the dictionary stack.
%
%   This procedure is applied to Maya fonts included via  mayaps.tmp
%
/NewFt{NF1 GDicts NFonts 3 dict dup begin/NumIC 5 index def/ISFx 0.65 def/ISFy 0.6 def end
       put GGDicts exch NFonts exch NF2 NF3 NFonts 1 sub def}bd
/NF1{NFonts GDicts length ge{/GDicts 32 GDicts ExtArr def/GGDicts 32 GGDicts ExtArr def}if}bd
/NF2{/NFonts NFonts 1 add def}bd/NF3{1 add dict dup begin put pop/iFont}bd
%----
%   NewF  is the version of NewFt the for case \special{header=font.mpf}

/NewF{SkF Si get dup GDicts exch 1 dict dup/Si Si 1 add def begin/NumIC
    6 index def end put GGDicts exch 3 2 roll NF3 SkF Si 1 sub get def}bd
%----
/SetInfixScaleFactors{GDicts iFont get begin/ISFy exch def/ISFx exch def end}bd
%----
%   Append  NFonts++  to the array  SkF
%
/SkipFont{/SkF 1 SkF ExtArr def SkF dup length 1 sub NFonts put NF1 NF2}bd
%----
%
/tmpini{/NewFont{NewFt}def}bd/tmpend{/NewFont{NewF}def}bd
tmpend/SkF[]def/Si 0 def
%----
%   n f  ->AddGlyphs->  -
%
%   Prepare for defining new glyphs to the font f.
%   Namely, increase the capacity of GDicts[f] by  n
%   (4g \le n < 5g where g is the number of glyphes to be add)
%   and put GGDicts[f] GDicts[f] on the top of the dict stack
%
/AddGlyphs{dup GGDicts exch get begin GDicts exch 2 copy get
    dup length 5 4 roll add dict copy dup begin put}bd

%----
/AG{SkF Si 1 sub get AddGlyphs}bd
%----
/GIni{GGDict begin gsave}bd/GEnd{grestore end}bd

/GDicts 32 array def/GGDicts 32 array def/NFonts 0 def
%=========================================================
% Glyph import support
%
%   default key f  -> imp1 ->  value
%
% where: (key,value)    is a key-value pair from GDicts[f]
%        value=default  if the key is unknown
%
/imp1{GDicts exch get dup 2 index known{begin cvx exec end exch pop}{pop pop}ie}bd
/imp{GDicts exch get dup 2 index known{begin cvx exec end pop}{pop pop Udf}ie}bd

end end
