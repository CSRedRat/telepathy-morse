/*
    Copyright (C) 2014 Alexandr Akulich <akulichalexander@gmail.com>

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef MORSE_TEXTCHANNEL_HPP
#define MORSE_TEXTCHANNEL_HPP

#include <QPointer>

#include <TelepathyQt/BaseChannel>

#include "CTelegramCore.hpp"

class MorseTextChannel;

typedef Tp::SharedPtr<MorseTextChannel> MorseTextChannelPtr;

class MorseTextChannel : public Tp::BaseChannelTextType
{
    Q_OBJECT
public:
    static MorseTextChannelPtr create(CTelegramCore *core, QObject *connection, Tp::BaseChannel *baseChannel, uint targetHandle, const QString &phone);
    virtual ~MorseTextChannel();

    QString sendMessageCallback(const Tp::MessagePartList &messageParts, uint flags, Tp::DBusError *error);

    void messageAcknowledgedCallback(const QString &messageId);

public slots:
    void whenContactChatStateComposingChanged(const QString &phone, bool composing);
    void whenMessageReceived(const QString &message, quint32 messageId);

protected slots:
    void sentMessageDeliveryStatusChanged(const QString &phone, quint64 messageId, TelegramNamespace::MessageDeliveryStatus status);

protected:
    void setChatState(uint state, Tp::DBusError *error);

private:
    MorseTextChannel(CTelegramCore *core, QObject *connection, Tp::BaseChannel *baseChannel, uint targetHandle, const QString &phone);

    QPointer<CTelegramCore> m_core;
    QObject *m_connection;

    QString m_phone;
    uint m_contactHandle;

    Tp::BaseChannelTextTypePtr m_channelTextType;
    Tp::BaseChannelMessagesInterfacePtr m_messagesIface;
    Tp::BaseChannelChatStateInterfacePtr m_chatStateIface;

};

#endif // MORSE_TEXTCHANNEL_HPP
