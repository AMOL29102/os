#!/bin/sh

# Function definitions outside the loop
create() {
    touch File3.txt
    echo "RollNo\t Name\t Phone-Number\t Email\t Address\n" > File3.txt
}

insert() {
    echo "RollNo:\c"
    read roll

    echo "Name:\c"
    read name
    while [ -z "$name" ]; do
        echo "Name cannot be empty. Please enter a valid name:\c"
        read name
    done

    echo "Phone:\c"
    while true
    do
        read phone
        if [ "$phone" -ge 1000000000 ] && [ "$phone" -le 9999999999 ]; then
            break
        else
            echo "\n Please enter a valid 10-digit number between 1000000000 and 9999999999 \nPhone:\c"
        fi
    done

    echo "Email:\c"
    while true
    do
        read email
        if echo "$email" | grep -q "@" && echo "$email" | grep -q "\."; then
            break
        else
            echo "Invalid email format. Please enter a valid email:\c"
        fi
    done

    echo "Address:\c"
    read address
    while [ -z "$address" ]; do
        echo "Address cannot be empty. Please enter a valid address:\c"
        read address
    done

    echo "$roll\t $name\t $phone\t $email\t $address" >> File3.txt
}

search() {
    echo "Enter the phone number to be searched:\c"
    read phon2
    grep -q "$phon2" File3.txt
    if [ $? -ne 0 ]; then
        echo "Record Not found"
    else
        grep -i -w "$phon2" File3.txt
        echo "Record found"
    fi
}

delete() {
    echo "Enter the phone number to be deleted:\c"
    read phon
    grep -q -w "$phon" File3.txt
    if [ $? -ne 0 ]; then
        echo "Record Not found"
    else
        grep -v -i -w "$phon" File3.txt > File2.txt
        mv File2.txt File3.txt
        echo "Record Deleted"
    fi
}

modify() {
    echo "Enter the phone number to be modified:\c"
    read phon1
    grep -q -w "$phon1" File3.txt
    if [ $? -ne 0 ]; then
        echo "Record Not found"
    else
        grep -v -i -w "$phon1" File3.txt > q.txt
        mv q.txt File3.txt
        insert
    fi
}

# Main menu inside an infinite loop
while true
do
    echo "MENU\n 1)Create address book\n 2)View address book\n 3)Insert a record\n 4)Search a record\n 5)Delete a record\n 6)Modify a record\n 7)Exit\n Enter your choice:\c"
    read choice

    case "$choice" in
        1) create ;;
        2) cat File3.txt ;;
        3)
            x=1
            while [ "$x" -eq 1 ]; do
                insert
                echo "Do you want to add another record? \nPress 1 to continue \nPress 2 to discontinue->\c"
                read x
            done
            ;;
        4) search ;;
        5) delete ;;
        6) modify ;;
        7) exit ;;
        *) echo "Invalid choice!!!" ;;
    esac
done
