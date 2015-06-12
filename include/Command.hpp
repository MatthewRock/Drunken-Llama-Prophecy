#ifndef COMMAND_HPP
#define COMMAND_HPP

class Player;

class Command
{
    public:
        virtual ~Command() = default;
        virtual void Execute() = 0;
        virtual void Draw() = 0;
    protected:
    private:
};
#endif // COMMAND_HPP
