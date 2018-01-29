#ifndef TC_TASKS_TEMPLATE_H
#define	TC_TASKS_TEMPLATE_H

// Timer 2
#define _75uSeg     ((unsigned long)(2)) // 100useg
#define _150uSeg    ((unsigned long)(2 * _75uSeg)) //200useg
#define _1mSeg      ((unsigned long)(_75uSeg * 10)) 
#define _10mSeg     ((unsigned long)(_1mSeg * 10))
#define _100mSeg    ((unsigned long)(_1mSeg * 100))
// Timer 4
// Timer 6

inline void InitTasks(void);
inline void MainTask();

inline void UpdateID(void);

void Delay(unsigned int);

#endif	/* TC_TASKS_TEMPLATE_H */