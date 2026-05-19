
// Based on https://stackoverflow.com/a/10526117

#define CAT(a, ...) a ## __VA_ARGS__

#define INC(x) CAT(INC_, x)
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INC_9 10
#define INC_10 11
#define INC_11 12
#define INC_12 13
#define INC_13 14
#define INC_14 15
#define INC_15 16
#define INC_16 17
#define INC_17 18
#define INC_18 19
#define INC_19 0

#define DEC(x) CAT(DEC_, x)
#define DEC_0 19
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8
#define DEC_10 9
#define DEC_11 10
#define DEC_12 11
#define DEC_13 12
#define DEC_14 13
#define DEC_15 14
#define DEC_16 15
#define DEC_17 16
#define DEC_18 17
#define DEC_19 18

#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__

#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)

#define NOT(x) CHECK(CAT(NOT_, x))
#define NOT_0 ~, 1,

#define COMPL(b) CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define BOOL(x) COMPL(NOT(x))

#define IF(c) CAT(IF_, c)
#define IF_0(t, ...) __VA_ARGS__
#define IF_1(t, ...) t

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__
#define EAT(...)

#define WHEN(c) IF(BOOL(c))(EXPAND, EAT)

#define PLUS_AUX(a, b) IF(BOOL(b))(OBSTRUCT(PLUS_INDIRECT)()(INC(a), DEC(b)), a)
#define PLUS_INDIRECT() PLUS_AUX
#define PLUS(a, b) EVAL(PLUS_AUX(a, b))

#define REPEAT(count, macro, ...)               \
  WHEN(count)                                   \
    (                                           \
      OBSTRUCT(REPEAT_INDIRECT) ()              \
      (                                         \
        DEC(count), macro, __VA_ARGS__          \
        )                                       \
      OBSTRUCT(macro)                           \
      (                                         \
        DEC(count), __VA_ARGS__                 \
        )                                       \
      )
#define REPEAT_INDIRECT() REPEAT

#define REPEAT_SEMI(count, macro, ...)          \
  WHEN(count)                                   \
    (                                           \
      OBSTRUCT(REPEAT_SEMI_INDIRECT) ()         \
      (                                         \
        DEC(count), macro, __VA_ARGS__          \
        )                                       \
      OBSTRUCT(macro)                           \
      (                                         \
        DEC(count), __VA_ARGS__                 \
        );                                      \
      )
#define REPEAT_SEMI_INDIRECT() REPEAT_SEMI

int main() {
  WHEN(1)("foo");  // "foo";
  WHEN(0)("bar");  // ;

  PLUS(5, 18);  // 3;    (23 % 20 = 3)

  EVAL(REPEAT_SEMI(19, PLUS_AUX, 5)); // for i in [0, 18], (i + 5) % 20
  //5; 6; 7; 8; 9; 10; 11; 12; 13; 14; 15; 16; 17; 18; 19; 0; 1; 2; 3;;

  return PLUS(3, 9);  // return 12;
}
