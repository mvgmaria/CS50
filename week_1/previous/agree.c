c
    char c = get_char("Do you agree? ");
    if (c == 'y' || c == 'Y') // we use single quotes for single char, and double quotes for strings. Also, the double pipe means "or"
    {
        printf("Agreed.\n)");

    }
    else if (c == 'n' || c == 'N')
    {
        printf("Not agreed.\n)");

    }
}
