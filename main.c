#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_YELLOW 14
#define COLOR_BLUE 9
#define COLOR_CYAN 11
#define COLOR_RESET 7

struct cartcalc
{
    int totalCost;
    int incartid[50];
    int incartprice[50];
    char incartname[50][30];
} cart0;

static int mark = 0;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printLine(int length)
{
    setColor(COLOR_CYAN);
    for(int i = 0; i < length; i++) printf("=");
    setColor(COLOR_RESET);
    printf("\n");
}


void printCentered(char* text, int width)
{
    int len = strlen(text);
    int padding = (width - len) / 2;
    for(int i = 0; i < padding; i++) printf(" ");
    printf("%s\n", text);
}

void productmenu()
{
    setColor(COLOR_YELLOW);
    printf("\n\nSelect an option from the menu : \n");
    setColor(COLOR_RESET);

    setColor(COLOR_GREEN);
    printf("1. Laptops\n");
    printf("2. Mobiles\n");
    printf("3. Headphones\n");
    printf("4. Computer Accessories\n");
    printf("5. Mobile Accessories\n");
    setColor(COLOR_BLUE);
    printf("6. Open Cart\n");
    setColor(COLOR_RED);
    printf("7. Checkout and Exit\n");
    setColor(COLOR_RESET);
}

void addtocart(int t, char nm[], int q)
{
    cart0.incartid[mark] = t;
    cart0.incartprice[mark] = q;
    strcpy(cart0.incartname[mark], nm);
    mark++;
}

void cart(char nm[])
{
    setColor(COLOR_CYAN);
    printf("\n");
    printLine(60);
    printf("                      %s's SHOPPING CART\n", nm);
    printLine(60);
    setColor(COLOR_RESET);

    for(int i = 0; i < mark; i++)
    {
        printf("%-3d | %-30s | Rs.%8d\n", cart0.incartid[i], cart0.incartname[i], cart0.incartprice[i]);
    }

    setColor(COLOR_YELLOW);
    printf("\nTotal Cost: Rs.%d\n", cart0.totalCost);
    setColor(COLOR_RESET);

    if(mark == 0)
    {
        setColor(COLOR_RED);
        printf("\nYour cart is empty!\n\n");
        setColor(COLOR_RESET);
    }
}

void editcart(char nm[])
{
    cart(nm);

    int ch, ch2, test = -1;

    if(mark == 0)
    {
        return;
    }
    else
    {
        setColor(COLOR_YELLOW);
        printf("\nOptions:\n");
        printf("1. Remove item from cart\n");
        printf("0. Close cart\n");
        printf("Enter your choice: ");
        setColor(COLOR_RESET);
        scanf("%d", &ch);

        if(ch == 1)
        {
            printf("\nEnter ID of item to remove: ");
            scanf("%d", &ch2);

            for(int i = 0; i < mark; i++)
                if(ch2 == cart0.incartid[i])
                    test = i;

            if(test != -1)
            {
                cart0.totalCost -= cart0.incartprice[test];
                mark--;
                setColor(COLOR_GREEN);
                printf("\n%s removed successfully!\n\n", cart0.incartname[test]);
                setColor(COLOR_RESET);
                for(int j = test; j < mark; j++)
                {
                    cart0.incartid[j] = cart0.incartid[j+1];
                    cart0.incartprice[j] = cart0.incartprice[j+1];
                    strcpy(cart0.incartname[j], cart0.incartname[j+1]);
                }
            }
            else
            {
                setColor(COLOR_RED);
                printf("\nItem not found in cart!\n\n");
                setColor(COLOR_RESET);
            }
        }
    }
}

void printProductHeader(char* category)
{
    setColor(COLOR_CYAN);
    printf("\n");
    printLine(60);
    printf("                      %s\n", category);
    printLine(60);
    setColor(COLOR_RESET);
    printf("ID  | %-30s | %10s\n", "Product Name", "Price (Rs.)");
    printLine(60);
}

void printProduct(int id, char* name, int price)
{
    printf("%-3d | %-30s | %10d\n", id, name, price);
}

void buylaptop()
{
    char laptops[9][30] = {"Dell Inspiron 3000","HP Pavilion x360","Dell G5 SE",
    "Asus TUF Gaming","Lenovo Legion","Acer Aspire 7","Acer Nitro 5",
    "Apple Macbook Air","HP 15s"};
    int priceLaptops[9] = {41900,68300,92900,64990,89890,49990,65990,122990,62500};
    int id[9], checkid = -1, p;

    printProductHeader("LAPTOPS");
    for(int i = 0; i < 9; i++)
    {
        id[i] = i+1;
        printProduct(id[i], laptops[i], priceLaptops[i]);
    }

    setColor(COLOR_YELLOW);
    printf("\nEnter ID of laptop to buy (0 to cancel): ");
    setColor(COLOR_RESET);
    scanf("%d", &checkid);

    if(checkid == 0) return;

    for(p = 0; p < 9; p++)
        if(id[p] == checkid)
            break;

    if(p < 9)
    {
        setColor(COLOR_GREEN);
        printf("\n%s added to cart!\n\n", laptops[p]);
        setColor(COLOR_RESET);
        cart0.totalCost += priceLaptops[p];
        addtocart(id[p], laptops[p], priceLaptops[p]);
        Sleep(1000); // Pause for 1 second
    }
    else
    {
        setColor(COLOR_RED);
        printf("\nInvalid ID! Please try again.\n\n");
        setColor(COLOR_RESET);
        Sleep(1000);
    }
}

void buymobile()
{
    char mobiles[9][30] = {"MI Note 10T Pro","Realme X3 Superzoom","Motorola Edge",
    "Asus Rog 3","Poco X2","Vivo V20","IPhone 12 Max Pro","Nokia 5.3",
    "OnePlus Nord Pro 5G"};
    int priceMobiles[9] = {49999,28999,64999,46999,16999,24990,119900,13999,29999};
    int id[9], checkid = -1, p;

    printProductHeader("MOBILE PHONES");
    for(int i = 0; i < 9; i++)
    {
        id[i] = i+10;
        printProduct(id[i], mobiles[i], priceMobiles[i]);
    }

    setColor(COLOR_YELLOW);
    printf("\nEnter ID of mobile to buy (0 to cancel): ");
    setColor(COLOR_RESET);
    scanf("%d", &checkid);

    if(checkid == 0) return;

    for(p = 0; p < 9; p++)
        if(id[p] == checkid)
            break;

    if(p < 9)
    {
        setColor(COLOR_GREEN);
        printf("\n%s added to cart!\n\n", mobiles[p]);
        setColor(COLOR_RESET);
        cart0.totalCost += priceMobiles[p];
        addtocart(id[p], mobiles[p], priceMobiles[p]);
        Sleep(1000);
    }
    else
    {
        setColor(COLOR_RED);
        printf("\nInvalid ID! Please try again.\n\n");
        setColor(COLOR_RESET);
        Sleep(1000);
    }
}

void buyheadphone()
{
    char headphones[9][30] = {"Philips SHP1900","Sony MDR-7506","Sennheiser HD 180",
    "Sony MDR-XB450AP","iBall EarWear Rock","Senheiser HD 206","Samson CH700",
    "Samson SR850","Panasonic RP-HT16"};
    int priceHeadphones[9] = {699,8790,2585,2250,887,999,1490,3735,3384};
    int id[9], checkid = -1, p;

    printProductHeader("HEADPHONES");
    for(int i = 0; i < 9; i++)
    {
        id[i] = i+19;
        printProduct(id[i], headphones[i], priceHeadphones[i]);
    }

    setColor(COLOR_YELLOW);
    printf("\nEnter ID of headphones to buy (0 to cancel): ");
    setColor(COLOR_RESET);
    scanf("%d", &checkid);

    if(checkid == 0) return;

    for(p = 0; p < 9; p++)
        if(id[p] == checkid)
            break;

    if(p < 9)
    {
        setColor(COLOR_GREEN);
        printf("\n%s added to cart!\n\n", headphones[p]);
        setColor(COLOR_RESET);
        cart0.totalCost += priceHeadphones[p];
        addtocart(id[p], headphones[p], priceHeadphones[p]);
        Sleep(1000);
    }
    else
    {
        setColor(COLOR_RED);
        printf("\nInvalid ID! Please try again.\n\n");
        setColor(COLOR_RESET);
        Sleep(1000);
    }
}

void buycompaccessory()
{
    char compaccs[9][30] = {"TP-Link Wifi Range Extender","Monitor Cable(DVI)","USB Hub QHL",
    "Monitor Cable","Card Reader","Blue-tooth Vista Ready","Logitech M-171 Mouse",
    "HP C2500 Keyboard and Mouse","1 TB Hard Disk"};
    int priceCompaccs[9] = {1200,150,55,125,350,160,825,790,2000};
    int id[9], checkid = -1, p;

    printProductHeader("COMPUTER ACCESSORIES");
    for(int i = 0; i < 9; i++)
    {
        id[i] = i+28;
        printProduct(id[i], compaccs[i], priceCompaccs[i]);
    }

    setColor(COLOR_YELLOW);
    printf("\nEnter ID of accessory to buy (0 to cancel): ");
    setColor(COLOR_RESET);
    scanf("%d", &checkid);

    if(checkid == 0) return;

    for(p = 0; p < 9; p++)
        if(id[p] == checkid)
            break;

    if(p < 9)
    {
        setColor(COLOR_GREEN);
        printf("\n%s added to cart!\n\n", compaccs[p]);
        setColor(COLOR_RESET);
        cart0.totalCost += priceCompaccs[p];
        addtocart(id[p], compaccs[p], priceCompaccs[p]);
        Sleep(1000);
    }
    else
    {
        setColor(COLOR_RED);
        printf("\nInvalid ID! Please try again.\n\n");
        setColor(COLOR_RESET);
        Sleep(1000);
    }
}

void buymobileaccessory()
{
    char mobileaccs[9][30] = {"MI 3i 10000 mAh PowerBank","iBall 10000 mAh PowerBank",
    "boAt USB cable","Backcover for Poco X2","Tempered Glass for Poco X2","Backcover for Vivo V20",
    "Tempered Glass for Poco F1","Mi USB cable","Ambrane USB Cable"};
    int priceMobileaccs[9] = {799,499,129,259,189,229,329,149,89};
    int id[9], checkid = -1, p;

    printProductHeader("MOBILE ACCESSORIES");
    for(int i = 0; i < 9; i++)
    {
        id[i] = i+37;
        printProduct(id[i], mobileaccs[i], priceMobileaccs[i]);
    }

    setColor(COLOR_YELLOW);
    printf("\nEnter ID of accessory to buy (0 to cancel): ");
    setColor(COLOR_RESET);
    scanf("%d", &checkid);

    if(checkid == 0) return;

    for(p = 0; p < 9; p++)
        if(id[p] == checkid)
            break;

    if(p < 9)
    {
        setColor(COLOR_GREEN);
        printf("\n%s added to cart!\n\n", mobileaccs[p]);
        setColor(COLOR_RESET);
        cart0.totalCost += priceMobileaccs[p];
        addtocart(id[p], mobileaccs[p], priceMobileaccs[p]);
        Sleep(1000);
    }
    else
    {
        setColor(COLOR_RED);
        printf("\nInvalid ID! Please try again.\n\n");
        setColor(COLOR_RESET);
        Sleep(1000);
    }
}

void main()
{
    system("cls");

    int choice;
    char name[50];
    setColor(COLOR_CYAN);
    printLine(60);
    printCentered("DIG YOUR RIG - COMPUTER HARDWARE STORE", 60);
    printLine(60);
    setColor(COLOR_RESET);

    printf("\nPlease enter your name: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    setColor(COLOR_GREEN);
    printf("\nHello %s, welcome to Dig Your Rig!\n", name);
    printf("Build your dream setup with us.\n");
    setColor(COLOR_RESET);
    Sleep(2000);

    while(1)
    {
        system("cls");
        setColor(COLOR_CYAN);
        printLine(60);
        printCentered("DIG YOUR RIG - MAIN MENU", 60);
        printLine(60);
        setColor(COLOR_RESET);

        productmenu();

        setColor(COLOR_YELLOW);
        printf("\nEnter your choice (1-7): ");
        setColor(COLOR_RESET);
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: buylaptop();
                    break;
            case 2: buymobile();
                    break;
            case 3: buyheadphone();
                    break;
            case 4: buycompaccessory();
                    break;
            case 5: buymobileaccessory();
                    break;
            case 6: editcart(name);
                    break;
            case 7:
                    system("cls");
                    setColor(COLOR_CYAN);
                    printLine(60);
                    printCentered("ORDER SUMMARY", 60);
                    printLine(60);
                    setColor(COLOR_RESET);

                    cart(name);

                    setColor(COLOR_GREEN);
                    printLine(60);
                    printf("\nThank you for shopping with Dig Your Rig!\n");
                    printf("Your total amount is Rs.%d\n", cart0.totalCost);
                    printf("We hope to see you again soon, %s!\n\n", name);
                    setColor(COLOR_RESET);
                    printLine(60);

                    exit(0);
                    break;
            default:
                    setColor(COLOR_RED);
                    printf("\nInvalid choice! Please enter a number between 1-7.\n");
                    setColor(COLOR_RESET);
                    Sleep(1000);
                    break;
        }
    }
}
