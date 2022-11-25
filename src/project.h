#ifndef _PROJECT__H_
#define _PROJECT__H_

/**
 * \brief Array of all drivers in the rally database
 */ 

/**
 * \brief Struct Driver and it's features
 */ 
typedef struct {
	char* lastName;    //!< name of the driver
    char* team;        //!< team of the driver
    int hours;         //!< hours driven
    int minutes;       //!< minutes driven
    int seconds;       //!< seonds driven
}Driver ;

/* Public functions in project.c */
// void memory_release(struct Driver *drivers, int size)
// struct Driver *add_driver(struct Driver *drivers, char* name, char* team, int i)
// void time_update(struct Driver *drivers, int i, int hours, int minutes, int seconds)
// void ordering(struct Driver *sortedDrivers, int i)
// void print_race(struct Driver *drivers, int i)
// void saveToFile(char *filename, struct Driver *drivers, int i)
// int count_rows(FILE *f)
// struct Driver  *download_info(char *filename, struct Driver *drivers, int i)
#endif //! _PROJECT__H_